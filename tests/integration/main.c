#include <libpq-fe.h>
#include "unity.h"
#include "db_pg_helper.h"
#include "user_pg_adapter_get_user_by_id_tests.h"

PGconn *conn = NULL;

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

    run_user_pg_adapter_get_user_by_id_tests();

    db_pg_shutdown(conn);
    return 0;
}
