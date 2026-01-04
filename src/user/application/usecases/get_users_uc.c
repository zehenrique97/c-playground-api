#include "get_users_uc.h"
#include "user.h"
#include "user_repo_port.h"
#include "user_uc_status.h"

UserUcStatus get_users_uc_handle(void *ctx, User **users, int *count) {
    GetUsersUc *get_users_uc = (GetUsersUc *) ctx;

    UserRepoStatus rc = get_users_uc->repo.get_users(get_users_uc->repo.ctx, users, count);

    return user_repo_status_to_uc_status(rc);
}