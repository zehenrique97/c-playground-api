#include "get_user_by_id_uc.h"
#include "user.h"
#include "user_repo_port.h"
#include "user_uc_status.h"

UserUcStatus get_user_by_id_uc_handle(void *ctx, int id, User *user) {
    GetUserByIdUc *get_user_by_id_uc = (GetUserByIdUc *) ctx;

    UserRepoStatus rc = get_user_by_id_uc->repo.get_user_by_id(get_user_by_id_uc->repo.ctx, id, user);

    return user_repo_status_to_uc_status(rc);
}