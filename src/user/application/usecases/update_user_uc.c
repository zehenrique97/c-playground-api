#include "update_user_uc.h"
#include "user.h"

int update_user_uc_handle(void *ctx, User *user) {
    UpdateUserUc *update_user_uc = (UpdateUserUc *) ctx;

    int rc = update_user_uc->repo.update_user(update_user_uc->repo.ctx, user);

    return rc;
}