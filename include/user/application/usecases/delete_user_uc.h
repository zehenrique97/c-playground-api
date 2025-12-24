#ifndef DELETE_USER_UC_H
#define DELETE_USER_UC_H

#include "user_repo_port.h"

typedef struct DeleteUserUc {
    UserRepoPort repo;
} DeleteUserUc;

int delete_user_uc_handle(void *ctx, int id);

#endif