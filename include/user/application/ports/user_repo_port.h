#ifndef USER_REPO_PORT_H
#define USER_REPO_PORT_H

#include "user.h"

typedef struct UserRepoPort {
    void *ctx;
    int (*get_users)(void *ctx, User **users, int *count);
    int (*get_user_by_id)(void *ctx, int id, User *user);
    int (*save_user)(void *ctx, User *user);
    int (*update_user)(void *ctx, User *user);
    int (*delete_user)(void *ctx, int id);
} UserRepoPort;

#endif