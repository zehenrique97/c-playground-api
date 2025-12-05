#include <libpq-fe.h>
#include <stdio.h>
#include "../include/app_context.h"

#define CONN_STRING "user=teste dbname=testedb password=teste123 host=database"

int app_init(AppContext *app) {
    app->db = PQconnectdb(CONN_STRING);

    if(PQstatus(app->db) == CONNECTION_OK)
        return 0;

    fprintf(stderr, "Could not establish connection with database: %s\n", PQerrorMessage(app->db));
    PQfinish(app->db);
    return 1;
}

void app_shutdown(AppContext *app) {
    if(app->db != NULL) {
        PQfinish(app->db);
        app->db = NULL;
    }
}