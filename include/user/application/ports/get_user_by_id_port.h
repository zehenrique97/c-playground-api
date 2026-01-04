#ifndef GET_USER_BY_ID_PORT_H
#define GET_USER_BY_ID_PORT_H

#include "user.h"
#include "user_uc_status.h"

typedef struct GetUserByIdPort {
    void *ctx;
    UserUcStatus (*handle)(void *ctx, int id, User *user);
} GetUserByIdPort;

#endif