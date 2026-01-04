#ifndef UPDATE_USER_PORT_H
#define UPDATE_USER_PORT_H

#include "user.h"
#include "user_uc_status.h"

typedef struct UpdateUserPort {
    void *ctx;
    UserUcStatus (*handle)(void *ctx, User *user);
} UpdateUserPort;

#endif