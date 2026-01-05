#include <stdbool.h>
#include "unity.h"
#include "user.h"
#include "user_repo_port.h"
#include "user_repo_port_mock.h"
#include "delete_user_tests.h"
#include "delete_user_uc.h"

void delete_user_user_deleted_return_ok() {
    int id = 1;
    UserRepoPortMock mock = {.delete_user_calls = 0};
    UserRepoPort repo = {.ctx = &mock, .delete_user = delete_user_mock};
    DeleteUserUc delete_user_uc = {.repo = repo};

    UserUcStatus rc = delete_user_uc_handle(&delete_user_uc, id);

    TEST_ASSERT_EQUAL_INT(USER_UC_SUCCESS, rc);
    TEST_ASSERT_EQUAL_INT(1, mock.delete_user_calls);
    TEST_ASSERT_EQUAL_INT(id, mock.deleted_id);
}

void delete_user_user_does_not_exist_return_not_found() {
    int id = 1;
    UserRepoPortMock mock = {.delete_user_calls = 0, .should_be_not_found = true};
    UserRepoPort repo = {.ctx = &mock, .delete_user = delete_user_mock};
    DeleteUserUc delete_user_uc = {.repo = repo};

    UserUcStatus rc = delete_user_uc_handle(&delete_user_uc, id);

    TEST_ASSERT_EQUAL_INT(USER_UC_NOT_FOUND, rc);
    TEST_ASSERT_EQUAL_INT(1, mock.delete_user_calls);
}

void delete_user_error_occurred_return_error() {
    int id = 1;
    UserRepoPortMock mock = {.delete_user_calls = 0, .should_throw_error = true};
    UserRepoPort repo = {.ctx = &mock, .delete_user = delete_user_mock};
    DeleteUserUc delete_user_uc = {.repo = repo};

    UserUcStatus rc = delete_user_uc_handle(&delete_user_uc, id);

    TEST_ASSERT_EQUAL_INT(USER_UC_ERROR, rc);
    TEST_ASSERT_EQUAL_INT(1, mock.delete_user_calls);
}

void run_delete_user_tests() {
    RUN_TEST(delete_user_user_deleted_return_ok);
    RUN_TEST(delete_user_user_does_not_exist_return_not_found);
    RUN_TEST(delete_user_error_occurred_return_error);
}