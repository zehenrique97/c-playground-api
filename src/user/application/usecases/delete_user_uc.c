#include "delete_user_uc.h"
#include "user_repo_port.h"
#include "user_uc_status.h"

UserUcStatus delete_user_uc_handle(void *ctx, int id) {
    DeleteUserUc *delete_user_uc = (DeleteUserUc *) ctx;

    UserRepoStatus rc = delete_user_uc->repo.delete_user(delete_user_uc->repo.ctx, id);

    return user_repo_status_to_uc_status(rc);
}