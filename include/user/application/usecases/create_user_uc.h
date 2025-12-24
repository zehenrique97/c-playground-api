#ifndef CREATE_USER_UC_H
#define CREATE_USER_UC_H

#include "user.h"
#include "user_repo_port.h"

typedef struct CreateUserUc {
    UserRepoPort repo;
} CreateUserUc;

int create_user_uc_handle(void *ctx, User *user);

#endif