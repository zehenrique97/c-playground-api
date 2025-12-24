#ifndef GET_USER_BY_ID_PORT_H
#define GET_USER_BY_ID_PORT_H

#include "user.h"

typedef struct GetUserByIdPort {
    void *ctx;
    int (*handle)(void *ctx, int id, User *user);
} GetUserByIdPort;

#endif