#include <stdbool.h>
#include "unity.h"
#include "user.h"
#include "user_repo_port.h"
#include "user_repo_port_mock.h"
#include "create_user_tests.h"
#include "create_user_uc.h"

void create_user_user_inserted_return_ok() {
    User user = {.id = 1, .name = "Jose", .age = 28};
    UserRepoPortMock mock = {.create_user_calls = 0};
    UserRepoPort repo = {.ctx = &mock, .save_user = create_user_mock};
    CreateUserUc create_user_uc = {.repo = repo};

    UserUcStatus rc = create_user_uc_handle(&create_user_uc, &user);

    TEST_ASSERT_EQUAL_INT(USER_UC_SUCCESS, rc);
    TEST_ASSERT_EQUAL_INT(user.id, mock.last_inserted.id);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(user.name, mock.last_inserted.name, sizeof(user.name));
    TEST_ASSERT_EQUAL_INT(user.age, mock.last_inserted.age);
    TEST_ASSERT_EQUAL_INT(1, mock.create_user_calls);
}

void create_user_error_occurred_return_error() {
    User user = {.id = 1, .name = "Jose", .age = 28};
    UserRepoPortMock mock = {.create_user_calls = 0, .should_throw_error = true};
    UserRepoPort repo = {.ctx = &mock, .save_user = create_user_mock};
    CreateUserUc create_user_uc = {.repo = repo};

    UserUcStatus rc = create_user_uc_handle(&create_user_uc, &user);

    TEST_ASSERT_EQUAL_INT(USER_UC_ERROR, rc);
    TEST_ASSERT_EQUAL_INT(1, mock.create_user_calls);
}

void run_create_user_tests() {
    RUN_TEST(create_user_user_inserted_return_ok);
    RUN_TEST(create_user_error_occurred_return_error);
}