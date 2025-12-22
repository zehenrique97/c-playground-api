#include <libpq-fe.h>
#include <stdlib.h>
#include <string.h>
#include "user_entity.h"

User *user_create() {
    User *user = malloc(sizeof(User));

    user->id = 0;
    strcpy(user->name, "");
    user->age = 0;

    return user;
}

void user_destroy(User *user) {
    free(user);
}