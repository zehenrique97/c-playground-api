#include <libpq-fe.h>
#include <stdlib.h>
#include <string.h>
#include "app_context.h"
#include "user_entity.h"
#include "user_repository.h"

int user_repository_get_users(AppContext *app, User **users, int *count) {
    PGresult *result = PQexec(app->db, "SELECT * FROM users;");
    if(PQresultStatus(result) != PGRES_TUPLES_OK) {
        PQclear(result);
        return 1;
    }

    int num_rows = PQntuples(result);
    if(num_rows == 0) {
        PQclear(result);
        *users = NULL;
        *count = 0;
        return 2;
    }

    User *user_rows = malloc(num_rows * sizeof(User));
    if(user_rows == NULL) {
        PQclear(result);
        return 1;
    }

    for (int i = 0; i < num_rows; i++) {
        user_rows[i].id = atoi(PQgetvalue(result, i, 0));
        strcpy(user_rows[i].name, PQgetvalue(result, i, 1));
        user_rows[i].age = atoi(PQgetvalue(result, i, 2));
    }

    *users = user_rows;
    *count = num_rows;
    PQclear(result);
    return 0;
}

int user_repository_get_user_by_id(AppContext *app, User *user) {
    char buffer[255];
    snprintf(buffer, sizeof(buffer), "SELECT * FROM users WHERE id=%d;", user->id);

    PGresult *result = PQexec(app->db, buffer);

    if(PQresultStatus(result) == PGRES_TUPLES_OK) {
        if(PQntuples(result) == 0) return 2;

        user->id = atoi(PQgetvalue(result, 0, 0));
        strcpy(user->name, PQgetvalue(result, 0, 1));
        user->age = atoi(PQgetvalue(result, 0, 2));

        return 0;
    }

    return 1;
}

int user_repository_create_user(AppContext *app, User *user) {
    char buffer[255];
    snprintf(buffer, sizeof(buffer), "INSERT INTO users(name, age) VALUES('%s', %d);", user->name, user->age);

    PGresult *result = PQexec(app->db, buffer);

    if(PQresultStatus(result) == PGRES_COMMAND_OK)
        return 0;

    return 1;
}

// TODO: Update e delete -> Mapear caso em que não há entidade na base

int user_repository_update_user(AppContext *app, User *user) {
    char buffer[255];
    snprintf(buffer, sizeof(buffer), "UPDATE users SET name='%s', age=%d WHERE id=%d;", user->name, user->age, user->id);

    PGresult *result = PQexec(app->db, buffer);

    if(PQresultStatus(result) == PGRES_COMMAND_OK)
        return 0;

    return 1;
}

int user_repository_delete_user(AppContext *app, int id) {
    char buffer[255];
    snprintf(buffer, sizeof(buffer), "DELETE FROM users WHERE id=%d;", id);

    PGresult *result = PQexec(app->db, buffer);

    if(PQresultStatus(result) == PGRES_COMMAND_OK)
        return 0;

    return 1;
}
