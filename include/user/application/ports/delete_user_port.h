#ifndef DELETE_USER_PORT_H
#define DELETE_USER_PORT_H

typedef struct DeleteUserPort {
    void *ctx;
    int (*handle)(void *ctx, int id);
} DeleteUserPort;

#endif