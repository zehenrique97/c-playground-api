#include "get_users_uc.h"
#include "user.h"

int get_users_uc_handle(void *ctx, User **users, int *count) {
    GetUsersUc *get_users_uc = (GetUsersUc *) ctx;

    int rc = get_users_uc->repo.get_users(get_users_uc->repo.ctx, users, count);

    return rc;
}