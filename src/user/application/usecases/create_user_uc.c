#include "create_user_uc.h"
#include "user.h"
#include "user_repo_port.h"
#include "user_uc_status.h"

UserUcStatus create_user_uc_handle(void *ctx, User *user) {
    CreateUserUc *create_user_uc = (CreateUserUc *) ctx;
  
    UserRepoStatus rc = create_user_uc->repo.save_user(create_user_uc->repo.ctx, user);

    return user_repo_status_to_uc_status(rc);
}