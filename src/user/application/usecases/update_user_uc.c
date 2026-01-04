#include "update_user_uc.h"
#include "user.h"
#include "user_repo_port.h"
#include "user_uc_status.h"

UserUcStatus update_user_uc_handle(void *ctx, User *user) {
    UpdateUserUc *update_user_uc = (UpdateUserUc *) ctx;

    UserRepoStatus rc = update_user_uc->repo.update_user(update_user_uc->repo.ctx, user);

    return user_repo_status_to_uc_status(rc);
}