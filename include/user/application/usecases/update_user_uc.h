#ifndef UPDATE_USER_UC_H
#define UPDATE_USER_UC_H

#include "user.h"
#include "user_repo_port.h"
#include "user_uc_status.h"

typedef struct UpdateUserUc {
    UserRepoPort repo;
} UpdateUserUc;

UserUcStatus update_user_uc_handle(void *ctx, User *user);

#endif