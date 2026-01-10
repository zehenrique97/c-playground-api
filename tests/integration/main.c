#include <libpq-fe.h>
#include <stdlib.h>
#include "unity.h"
#include "db_pg_helper.h"
#include "user_pg_adapter_get_users_tests.h"
#include "user_pg_adapter_get_user_by_id_tests.h"
#include "user_pg_adapter_save_user_tests.h"
#include "user_pg_adapter_update_user_tests.h"
#include "user_pg_adapter_delete_user_tests.h"
#include "pg_pool.h"

PGconn *conn = NULL;
PgPool *pg_pool = NULL;

void setUp() {
    PQclear(PQexec(conn, "BEGIN;"));
}

void tearDown() {
    PQclear(PQexec(conn, "ROLLBACK;"));
}

int main() {
    db_pg_init(&conn);
    db_pg_create_table(conn, "users (id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY, name VARCHAR(255), age INT)");
    db_pg_insert(conn, "users (name, age)", "('User1', 20),('User2', 30),('User3', 40)");

    pg_pool = malloc(sizeof(PgPool *));

    pg_pool_init(pg_pool, 2);

    UNITY_BEGIN();
    run_user_pg_adapter_get_users_tests();
    run_user_pg_adapter_get_user_by_id_tests();
    run_user_pg_adapter_save_user_tests();
    run_user_pg_adapter_update_user_tests();
    run_user_pg_adapter_delete_user_tests();
    int result = UNITY_END();

    db_pg_delete_all(conn, "users");
    db_pg_shutdown(conn);

    pg_pool_destroy(pg_pool);
    
    return result;
}
