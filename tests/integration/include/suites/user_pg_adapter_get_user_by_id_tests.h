#ifndef USER_PG_ADAPTER_GET_USER_BY_ID_TESTS_H
#define USER_PG_ADAPTER_GET_USER_BY_ID_TESTS_H

#include <libpq-fe.h>

extern PGconn *conn;

void run_user_pg_adapter_get_user_by_id_tests(void);

#endif
