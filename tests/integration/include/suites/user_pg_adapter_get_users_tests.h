#ifndef USER_PG_ADAPTER_GET_USERS_TESTS_H
#define USER_PG_ADAPTER_GET_USERS_TESTS_H

#include "pg_pool.h"

extern PgPool *pg_pool;
extern PGconn *conn;

void run_user_pg_adapter_get_users_tests();

#endif