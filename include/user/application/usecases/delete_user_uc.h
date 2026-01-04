#ifndef DELETE_USER_UC_H
#define DELETE_USER_UC_H

#include "user_repo_port.h"
#include "user_uc_status.h"

typedef struct DeleteUserUc {
    UserRepoPort repo;
} DeleteUserUc;

UserUcStatus delete_user_uc_handle(void *ctx, int id);

#endif