#ifndef PG_POOL_H
#define PG_POOL_H

#include <libpq-fe.h>
#include <pthread.h>

typedef struct PgPool {
    PGconn **conns;
    int *available;
    int size;
    int available_count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} PgPool;

int pg_pool_init(PgPool *pool, const char *conninfo, int size);
PGconn *pg_pool_acquire(PgPool *pool);
void pg_pool_release(PgPool *pool, PGconn *conn);
void pg_pool_shutdown(PgPool *pool);

#endif
