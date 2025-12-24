#ifndef CREATE_USER_PORT_H
#define CREATE_USER_PORT_H

#include "user.h"

typedef struct CreateUserPort {
    void *ctx;
    int (*handle)(void *ctx, User *user);
} CreateUserPort;

#endif