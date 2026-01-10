#include <pthread.h>
#include <stdlib.h>
#include "pg_pool.h"

#define CONN_STRING "user=teste dbname=testedb password=teste123 host=localhost"

int pg_pool_init(PgPool *pool, int capacity) {
    pool->capacity = capacity;
    pool->top = capacity;

    pool->conns = (PGconn **) calloc((size_t) capacity, sizeof(PGconn *));
    pool->free_conns_indexes = (int *) calloc((size_t) capacity, sizeof(int));

    if(!pool->conns || !pool->free_conns_indexes) return 1;

    for(int i = 0; i < capacity; i++) {
        pool->conns[i] = PQconnectdb(CONN_STRING);

         if(PQstatus(pool->conns[i]) != CONNECTION_OK) {
            fprintf(stderr, "Could not establish connection with database: %s\n", PQerrorMessage(pool->conns[i]));
            
            for(int j = 0; j < capacity; j++) {if (pool->conns[j]) PQfinish(pool->conns[j]);}
            free(pool->conns);
            free(pool->free_conns_indexes);

            return 1;
         }

        pool->free_conns_indexes = i;
    }

    pthread_mutex_init(&pool->mutex, NULL);
    pthread_cond_init(&pool->cond, NULL);

    return 0;
}

void pg_pool_destroy(PgPool *pool) {
    for(int i = 0; i < pool->capacity; i++) {if (pool->conns[i]) PQfinish(pool->conns[i]);}
    pthread_mutex_destroy(&pool->mutex);
    pthread_cond_destroy(&pool->cond);
    free(pool->conns);
    free(pool->free_conns_indexes);
}

PgPoolHandler pg_pool_acquire(PgPool *pool) {
    pthread_mutex_lock(&pool->mutex);

    while(pool->top == 0) {
        pthread_cond_wait(&pool->cond, &pool->mutex);
    }

    pool->top--;
    int index = pool->free_conns_indexes[pool->top];

    PgPoolHandler handler = {.pool = pool->conns[index], .pool_index = index};

    pthread_mutex_unlock(&pool->mutex);

    return handler;
}

void pg_pool_release(PgPool *pool, PgPoolHandler *handler) {
    pthread_mutex_lock(&pool->mutex);

    pool->free_conns_indexes[pool->top] = handler->pool_index;
    pool->top++;

    pthread_cond_signal(&pool->cond);

    pthread_mutex_unlock(&pool->mutex);
}