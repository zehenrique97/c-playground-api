#include "user_repo_port.h"
#include "user_uc_status.h"

UserUcStatus user_repo_status_to_uc_status(UserRepoStatus repo_status) {
    switch (repo_status)
    {
        case USER_REPO_SUCCESS:
            return USER_UC_SUCCESS;
        case USER_REPO_NOT_FOUND:
            return USER_UC_NOT_FOUND;
        default:
            return USER_UC_ERROR;
    }
}