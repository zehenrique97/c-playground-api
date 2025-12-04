#include <libpq-fe.h>
#include <stdlib.h>
#include <string.h>
#include "../include/app_context.h"
#include "../include/user_entity.h"
#include "../include/user_repository.h"
#include "../include/user_types.h"

int get_users_entity(AppContext *app, UserEntity **users, int *count) {
    PGresult *result = PQexec(app->db, "SELECT * FROM users;");
    int num_rows = PQntuples(result);

    *count = num_rows;

    if(PQresultStatus(result) == PGRES_TUPLES_OK) {
        if(num_rows == 0) {
            PQclear(result);
            return 2;
        }

        UserEntity *users_malloc = malloc(num_rows * sizeof(UserEntity));

        for (int i = 0; i < num_rows; i++) {
            users_malloc[i].id = atoi(PQgetvalue(result, i, 0));
            users_malloc[i].name = strdup(PQgetvalue(result, i, 1));
            users_malloc[i].age = atoi(PQgetvalue(result, i, 2));
        }

        *users = users_malloc;
        PQclear(result);
        return 0;
    }
    PQclear(result);
    return 1;
}

int get_user_entity_by_id(AppContext *app, UserEntity *target, int id) {
    char buffer[255];
    snprintf(buffer, sizeof(buffer), "SELECT * FROM users WHERE id=%d;", id);

    PGresult *result = PQexec(app->db, buffer);

    if(PQresultStatus(result) == PGRES_TUPLES_OK) {
        if(PQntuples(result) == 0) return 2;

        *target = map_query_to_entity(result);
        return 0;
    }

    return 1;
}

int create_user_entity(AppContext *app, UserEntity *user) {
    char buffer[255];
    snprintf(buffer, sizeof(buffer), "INSERT INTO users(name, age) VALUES('%s', %d);", user->name, user->age);

    PGresult *result = PQexec(app->db, buffer);

    if(PQresultStatus(result) == PGRES_COMMAND_OK)
        return 0;

    return 1;
}

// TODO: Update e delete -> Mapear caso em que não há entidade na base

int update_user_entity(AppContext *app, UserEntity *user) {
    char buffer[255];
    snprintf(buffer, sizeof(buffer), "UPDATE users SET name='%s', age=%d WHERE id=%d;", user->name, user->age, user->id);

    PGresult *result = PQexec(app->db, buffer);

    if(PQresultStatus(result) == PGRES_COMMAND_OK)
        return 0;

    return 1;
}

int delete_user_entity(AppContext *app, int id) {
    char buffer[255];
    snprintf(buffer, sizeof(buffer), "DELETE FROM users WHERE id=%d;", id);

    PGresult *result = PQexec(app->db, buffer);

    if(PQresultStatus(result) == PGRES_COMMAND_OK)
        return 0;

    return 1;
}