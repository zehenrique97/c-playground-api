#ifndef GET_USERS_PORT_H
#define GET_USERS_PORT_H

#include "user.h"

typedef struct GetUsersPort {
    void *ctx;
    int (*handle)(void *ctx, User **users, int *count);
} GetUsersPort;

#endif