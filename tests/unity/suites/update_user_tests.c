#include <stdbool.h>
#include "unity.h"
#include "user.h"
#include "user_repo_port.h"
#include "user_repo_port_mock.h"
#include "update_user_tests.h"
#include "update_user_uc.h"

void update_user_user_updated_return_ok() {
    User user = {.id = 1, .name = "Jose", .age = 28};
    UserRepoPortMock mock = {.update_user_calls = 0};
    UserRepoPort repo = {.ctx = &mock, .update_user = updated_user_mock};
    UpdateUserUc update_user_uc = {.repo = repo};

    UserUcStatus rc = update_user_uc_handle(&update_user_uc, &user);

    TEST_ASSERT_EQUAL_INT(USER_UC_SUCCESS, rc);
    TEST_ASSERT_EQUAL_INT(user.id, mock.last_updated.id);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(user.name, mock.last_updated.name, sizeof(user.name));
    TEST_ASSERT_EQUAL_INT(user.age, mock.last_updated.age);
    TEST_ASSERT_EQUAL_INT(1, mock.update_user_calls);
}

void update_user_user_does_not_exist_return_not_found() {
    User user = {.id = 1, .name = "Jose", .age = 28};
    UserRepoPortMock mock = {.update_user_calls = 0, .should_be_not_found = true};
    UserRepoPort repo = {.ctx = &mock, .update_user = updated_user_mock};
    UpdateUserUc update_user_uc = {.repo = repo};

    UserUcStatus rc = update_user_uc_handle(&update_user_uc, &user);

    TEST_ASSERT_EQUAL_INT(USER_UC_NOT_FOUND, rc);
    TEST_ASSERT_EQUAL_INT(1, mock.update_user_calls);
}

void update_user_error_ocurred_return_error() {
    User user = {.id = 1, .name = "Jose", .age = 28};
    UserRepoPortMock mock = {.update_user_calls = 0, .should_throw_error = true};
    UserRepoPort repo = {.ctx = &mock, .update_user = updated_user_mock};
    UpdateUserUc update_user_uc = {.repo = repo};

    UserUcStatus rc = update_user_uc_handle(&update_user_uc, &user);

    TEST_ASSERT_EQUAL_INT(USER_UC_ERROR, rc);
    TEST_ASSERT_EQUAL_INT(1, mock.update_user_calls);
}

void run_update_user_tests() {
    RUN_TEST(update_user_user_updated_return_ok);
    RUN_TEST(update_user_user_does_not_exist_return_not_found);
    RUN_TEST(update_user_error_ocurred_return_error);
}