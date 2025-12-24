#ifndef UPDATE_USER_PORT_H
#define UPDATE_USER_PORT_H

#include "user.h"

typedef struct UpdateUserPort {
    void *ctx;
    int (*handle)(void *ctx, User *user);
} UpdateUserPort;

#endif