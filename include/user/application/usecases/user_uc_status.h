#ifndef USER_UC_STATUS_H
#define USER_UC_STATUS_H

#include "user_repo_port.h"

typedef enum UserUcStatus {
    USER_UC_SUCCESS,
    USER_UC_ERROR,
    USER_UC_NOT_FOUND,
} UserUcStatus;

UserUcStatus user_repo_status_to_uc_status(UserRepoStatus repo_status);

#endif