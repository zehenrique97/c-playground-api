#ifndef GET_USERS_UC_H
#define GET_USERS_UC_H

#include "user.h"
#include "user_repo_port.h"
#include "user_uc_status.h"

typedef struct GetUsersUc {
    UserRepoPort repo;
} GetUsersUc;

UserUcStatus get_users_uc_handle(void *ctx, User **users, int *count);

#endif
