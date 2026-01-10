#ifndef PG_POOL_H
#define PG_POOL_H

#include <libpq-fe.h>
#include <pthread.h>

typedef struct PgPool {
    PGconn **conns;
    int *free_conns_indexes;
    int top;
    int capacity;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} PgPool;

typedef struct PgPoolHandler {
    PGconn *conn;
    int pool_index;
} PgPoolHandler;

typedef enum PgPoolStatus {
    PG_POOL_SUCCESS,
    PG_POOL_ERROR
} PgPoolStatus;

PgPoolStatus pg_pool_init(PgPool *pool, int capacity);

void pg_pool_destroy(PgPool *pool);

PgPoolHandler pg_pool_acquire(PgPool *pool);

void pg_pool_release(PgPool *pool, PgPoolHandler *handler);

#endif