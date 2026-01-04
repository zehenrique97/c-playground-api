#ifndef CREATE_USER_PORT_H
#define CREATE_USER_PORT_H

#include "user.h"
#include "user_uc_status.h"

typedef struct CreateUserPort {
    void *ctx;
    UserUcStatus (*handle)(void *ctx, User *user);
} CreateUserPort;

#endif