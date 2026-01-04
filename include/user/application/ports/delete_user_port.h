#ifndef DELETE_USER_PORT_H
#define DELETE_USER_PORT_H

#include "user_uc_status.h"

typedef struct DeleteUserPort {
    void *ctx;
    UserUcStatus (*handle)(void *ctx, int id);
} DeleteUserPort;

#endif