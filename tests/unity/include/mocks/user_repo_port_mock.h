#ifndef USER_REPO_PORT_MOCK_H
#define USER_REPO_PORT_MOCK_H

#include <stdbool.h>
#include "user.h"
#include "user_repo_port.h"

typedef struct UserRepoPortMock {
    int get_users_calls;
    int get_user_by_id_calls;
    int create_user_calls;
    int update_user_calls;
    int delete_user_calls;
    User returned_user_list[3];
    User returned_user;
    int returned_id;
    User last_inserted;
    User last_updated;
    int deleted_id;
    bool should_be_not_found;
    bool should_throw_error;
} UserRepoPortMock;

UserRepoStatus get_users_mock(void *ctx, User **users, int *count);
UserRepoStatus get_user_by_id_mock(void *ctx, int id, User *user);
UserRepoStatus create_user_mock(void *ctx, User *user);
UserRepoStatus updated_user_mock(void *ctx, User *user);
UserRepoStatus delete_user_mock(void *ctx, int id);

#endif