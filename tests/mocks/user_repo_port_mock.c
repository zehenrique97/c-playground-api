#include "user_repo_port_mock.h"
#include "user.h"
#include "user_repo_port.h"

UserRepoStatus get_users_mock(void *ctx, User **users, int *count) {
    UserRepoPortMock *repo = (UserRepoPortMock *) ctx;

    repo->get_users_calls++;

    if(repo->should_be_not_found) {
        *count = 0;
        return USER_REPO_NOT_FOUND;
    }

    if(repo->should_throw_error) return USER_REPO_ERROR;

    *users = repo->returned_user_list;
    *count = sizeof(repo->returned_user_list) / sizeof(User);

    return USER_REPO_SUCCESS;
}

UserRepoStatus get_user_by_id_mock(void *ctx, int id, User *user) {
    UserRepoPortMock *repo = (UserRepoPortMock *) ctx;

    repo->get_user_by_id_calls++;

    if(repo->should_be_not_found) return USER_REPO_NOT_FOUND;

    if(repo->should_throw_error) return USER_REPO_ERROR;

    *user = repo->returned_user;
    repo->returned_id = id;

    return USER_REPO_SUCCESS;
}

UserRepoStatus create_user_mock(void *ctx, User *user) {
    UserRepoPortMock *repo = (UserRepoPortMock *) ctx;

    repo->create_user_calls++;

    if(repo->should_throw_error) return USER_REPO_ERROR;

    repo->last_inserted = *user;

    return USER_REPO_SUCCESS;
}

UserRepoStatus updated_user_mock(void *ctx, User *user) {
    UserRepoPortMock *repo = (UserRepoPortMock *) ctx;

    repo->update_user_calls++;

    if(repo->should_be_not_found) return USER_REPO_NOT_FOUND;

    if(repo->should_throw_error) return USER_REPO_ERROR;

    repo->last_updated = *user;

    return USER_REPO_SUCCESS;
}

UserRepoStatus delete_user_mock(void *ctx, int id) {
    UserRepoPortMock *repo = (UserRepoPortMock *) ctx;

    repo->delete_user_calls++;

    if(repo->should_be_not_found) return USER_REPO_NOT_FOUND;

    if(repo->should_throw_error) return USER_REPO_ERROR;

    repo->deleted_id = id;

    return USER_REPO_SUCCESS;
}