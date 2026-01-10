#include <string.h>
#include "db_pg_helper.h"

#define CONN_STRING "user=teste dbname=testedb password=teste123 host=localhost"

int db_pg_init(PGconn **conn) {
    printf("Connecting to DB on localhost:5432...\n");
    *conn = PQconnectdb(CONN_STRING);
    if(PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Could not establish connection with database: %s\n", PQerrorMessage(*conn));
        PQfinish(*conn);
        return 1;
    }
    printf("Connection established\n");
    return 0;
}

int db_pg_create_table(PGconn *conn, char *schema) {
    char buffer[500];
    snprintf(buffer, sizeof(buffer), "CREATE TABLE %s;", schema);

    printf("Creating table %s\n", schema);
    PGresult *result = PQexec(conn, buffer);

    if(PQresultStatus(result) != PGRES_COMMAND_OK) {
        printf("Error while creating table: %s\n", PQerrorMessage(conn));
        PQclear(result);
        return 1;
    }
    return 0;
}

int db_pg_insert(PGconn *conn, char *table, char *parameters) {
    char buffer[500];
    snprintf(buffer, sizeof(buffer), "INSERT INTO %s VALUES %s;", table, parameters);

    printf("Inserting rows: %s\n", parameters);
    PGresult *result = PQexec(conn, buffer);

    if(PQresultStatus(result) != PGRES_COMMAND_OK) {
        printf("Error while executing command %s\n", PQerrorMessage(conn));
        PQclear(result);
        return 1;
    }
    return 0;
}

int db_pg_delete_all(PGconn *conn, char *table) {
    char buffer[500];
    snprintf(buffer, sizeof(buffer), "DELETE FROM %s;", table);

    PGresult *result = PQexec(conn, buffer);

    if(PQresultStatus(result) != PGRES_COMMAND_OK) {
        printf("Error while executing command %s\n", PQerrorMessage(conn));
        PQclear(result);
        return 1;
    }
    return 0;
}

int db_pg_delete(PGconn *conn, char *table, int id) {
    char buffer[500];
    snprintf(buffer, sizeof(buffer), "DELETE FROM %s WHERE id=%d;", table, id);

    PGresult *result = PQexec(conn, buffer);

    if(PQresultStatus(result) != PGRES_COMMAND_OK) {
        printf("Error while executing command %s\n", PQerrorMessage(conn));
        PQclear(result);
        return 1;
    }
    return 0;
}

int db_pg_shutdown(PGconn *conn) {
    if(conn != NULL) {
        PQfinish(conn);
        conn = NULL;
    }
}
