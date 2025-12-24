#include "delete_user_uc.h"

int delete_user_uc_handle(void *ctx, int id) {
    DeleteUserUc *delete_user_uc = (DeleteUserUc *) ctx;

    int rc = delete_user_uc->repo.delete_user(delete_user_uc->repo.ctx, id);

    return rc;
}