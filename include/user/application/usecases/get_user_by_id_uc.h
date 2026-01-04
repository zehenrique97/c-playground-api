#ifndef GET_USER_BY_ID_UC_H
#define GET_USER_BY_ID_UC_H

#include "user.h"
#include "user_repo_port.h"
#include "user_uc_status.h"

typedef struct GetUserByIdUc {
    UserRepoPort repo;
} GetUserByIdUc;

UserUcStatus get_user_by_id_uc_handle(void *ctx, int id, User *user);

#endif