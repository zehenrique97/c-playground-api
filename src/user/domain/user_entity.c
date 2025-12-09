#include <libpq-fe.h>
#include <stdlib.h>
#include "user_entity.h"

User *user_create() {
    User *user = malloc(sizeof(User));

    user->id = 0;
    user->name = "";
    user->age = 0;

    return user;
}

void user_destroy(User *user) {
    free(user);
}

void query_to_user(User *user, PGresult *result, int row_number) {
    user->id = atoi(PQgetvalue(result, row_number, 0));
    user->name = PQgetvalue(result, row_number, 1);
    user->age = atoi(PQgetvalue(result, row_number, 2));
}