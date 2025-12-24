#include "create_user_uc.h"
#include "user.h"

int create_user_uc_handle(void *ctx, User *user) {
    CreateUserUc *create_user_uc = (CreateUserUc *) ctx;
  
    int rc = create_user_uc->repo.save_user(create_user_uc->repo.ctx, user);

    return rc;
}