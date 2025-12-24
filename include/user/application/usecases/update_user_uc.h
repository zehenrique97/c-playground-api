#ifndef UPDATE_USER_UC_H
#define UPDATE_USER_UC_H

#include "user.h"
#include "user_repo_port.h"

typedef struct UpdateUserUc {
    UserRepoPort repo;
} UpdateUserUc;

int update_user_uc_handle(void *ctx, User *user);

#endif