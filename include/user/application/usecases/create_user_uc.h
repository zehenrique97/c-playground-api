#ifndef CREATE_USER_UC_H
#define CREATE_USER_UC_H

#include "user.h"
#include "user_repo_port.h"
#include "user_uc_status.h"

typedef struct CreateUserUc {
    UserRepoPort repo;
} CreateUserUc;

UserUcStatus create_user_uc_handle(void *ctx, User *user);

#endif