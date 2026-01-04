#ifndef GET_USERS_PORT_H
#define GET_USERS_PORT_H

#include "user.h"
#include "user_uc_status.h"

typedef struct GetUsersPort {
    void *ctx;
    UserUcStatus (*handle)(void *ctx, User **users, int *count);
} GetUsersPort;

#endif