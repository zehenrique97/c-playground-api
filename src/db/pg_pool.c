#include <stdlib.h>
#include "pg_pool.h"

int pg_pool_init(PgPool *pool, const char *conninfo, int size) {
    if (pool == NULL || conninfo == NULL || size <= 0) return 1;

    pool->conns = calloc(size, sizeof(PGconn *));
    pool->available = calloc(size, sizeof(int));
    if (pool->conns == NULL || pool->available == NULL) {
        free(pool->conns);
        free(pool->available);
        return 1;
    }

    pool->size = size;
    pool->available_count = size;
    pthread_mutex_init(&pool->mutex, NULL);
    pthread_cond_init(&pool->cond, NULL);

    for (int i = 0; i < size; i++) {
        pool->conns[i] = PQconnectdb(conninfo);
        if (pool->conns[i] == NULL || PQstatus(pool->conns[i]) != CONNECTION_OK) {
            for (int j = 0; j <= i; j++) {
                if (pool->conns[j] != NULL) {
                    PQfinish(pool->conns[j]);
                }
            }
            free(pool->conns);
            free(pool->available);
            pthread_mutex_destroy(&pool->mutex);
            pthread_cond_destroy(&pool->cond);
            return 1;
        }
        pool->available[i] = i;
    }

    return 0;
}

PGconn *pg_pool_acquire(PgPool *pool) {
    if (pool == NULL) return NULL;

    pthread_mutex_lock(&pool->mutex);
    while (pool->available_count == 0) {
        pthread_cond_wait(&pool->cond, &pool->mutex);
    }
    int idx = pool->available[--pool->available_count];
    PGconn *conn = pool->conns[idx];
    pthread_mutex_unlock(&pool->mutex);
    return conn;
}

void pg_pool_release(PgPool *pool, PGconn *conn) {
    if (pool == NULL || conn == NULL) return;

    pthread_mutex_lock(&pool->mutex);
    int idx = -1;
    for (int i = 0; i < pool->size; i++) {
        if (pool->conns[i] == conn) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        pthread_mutex_unlock(&pool->mutex);
        return;
    }

    for (int i = 0; i < pool->available_count; i++) {
        if (pool->available[i] == idx) {
            pthread_mutex_unlock(&pool->mutex);
            return;
        }
    }

    pool->available[pool->available_count++] = idx;
    pthread_cond_signal(&pool->cond);
    pthread_mutex_unlock(&pool->mutex);
}

void pg_pool_shutdown(PgPool *pool) {
    if (pool == NULL) return;

    for (int i = 0; i < pool->size; i++) {
        if (pool->conns[i] != NULL) {
            PQfinish(pool->conns[i]);
        }
    }
    free(pool->conns);
    free(pool->available);
    pthread_mutex_destroy(&pool->mutex);
    pthread_cond_destroy(&pool->cond);

    pool->conns = NULL;
    pool->available = NULL;
    pool->size = 0;
    pool->available_count = 0;
}
