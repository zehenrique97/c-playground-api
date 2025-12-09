#include <libpq-fe.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "user_entity.h"

UserEntity map_query_to_entity(PGresult *result) {
    UserEntity user = {
        .id = atoi(PQgetvalue(result, 0, 0)),
        .name = PQgetvalue(result, 0, 1),
        .age = atoi(PQgetvalue(result, 0, 2))
    };

    return user;
}