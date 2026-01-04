#ifndef USER_REPO_PORT_H
#define USER_REPO_PORT_H

#include "user.h"
typedef enum UserRepoStatus {
    USER_REPO_SUCCESS,
    USER_REPO_ERROR,
    USER_REPO_NOT_FOUND
} UserRepoStatus;

typedef struct UserRepoPort {
    void *ctx;
    UserRepoStatus (*get_users)(void *ctx, User **users, int *count);
    UserRepoStatus (*get_user_by_id)(void *ctx, int id, User *user);
    UserRepoStatus (*save_user)(void *ctx, User *user);
    UserRepoStatus (*update_user)(void *ctx, User *user);
    UserRepoStatus (*delete_user)(void *ctx, int id);
} UserRepoPort;

#endif