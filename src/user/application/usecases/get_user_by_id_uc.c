#include "get_user_by_id_uc.h"
#include "user.h"

int get_user_by_id_uc_handle(void *ctx, int id, User *user) {
    GetUserByIdUc *get_user_by_id_uc = (GetUserByIdUc *) ctx;

    int rc = get_user_by_id_uc->repo.get_user_by_id(get_user_by_id_uc->repo.ctx, id, user);

    return rc;
}