#include <stdbool.h>
#include "unity.h"
#include "user_repo_port_mock.h"
#include "user_repo_port.h"
#include "get_user_by_id_uc.h"

void get_user_by_id_user_exists_returns_ok() {
    // Arrange
    User user = {.id = 1, .name = "Jose", .age = 20};
    UserRepoPortMock mock = {.get_user_by_id_calls = 0, .returned_user = user};
    UserRepoPort repo = {.ctx = &mock, .get_user_by_id = get_user_by_id_mock};
    GetUserByIdUc get_user_by_id_uc = {.repo = repo};

    // Act
    UserUcStatus rc = get_user_by_id_uc_handle(&get_user_by_id_uc, user.id, &user);

    // Assert
    TEST_ASSERT_EQUAL_INT(USER_UC_SUCCESS, rc);
    TEST_ASSERT_EQUAL_INT(user.id, mock.returned_id);
    TEST_ASSERT_EQUAL_INT(user.id, mock.returned_user.id);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(user.name, mock.returned_user.name, sizeof(user.name));
    TEST_ASSERT_EQUAL_INT(user.age, mock.returned_user.age);
    TEST_ASSERT_EQUAL_INT(1, mock.get_user_by_id_calls);
}

void get_user_by_id_user_does_not_exist_returns_not_found() {
    User user = {.id = 1, .name = "Jose", .age = 20};
    UserRepoPortMock mock = {.get_user_by_id_calls = 0, .should_be_not_found = true};
    UserRepoPort repo = {.ctx = &mock, .get_user_by_id = get_user_by_id_mock};
    GetUserByIdUc get_user_by_id_uc = {.repo = repo};

    UserUcStatus rc = get_user_by_id_uc_handle(&get_user_by_id_uc, user.id, &user);

    TEST_ASSERT_EQUAL_INT(USER_UC_NOT_FOUND, rc);
    TEST_ASSERT_EQUAL_INT(1, mock.get_user_by_id_calls);
}

void get_user_by_id_error_ocourred_return_error() {
    User user = {.id = 1, .name = "Jose", .age = 20};
    UserRepoPortMock mock = {.get_user_by_id_calls = 0, .should_throw_error = true};
    UserRepoPort repo = {.ctx = &mock, .get_user_by_id = get_user_by_id_mock};
    GetUserByIdUc get_user_by_id_uc = {.repo = repo};

    UserUcStatus rc = get_user_by_id_uc_handle(&get_user_by_id_uc, user.id, &user);

    TEST_ASSERT_EQUAL_INT(USER_UC_ERROR, rc);
    TEST_ASSERT_EQUAL_INT(1, mock.get_user_by_id_calls);
}

void run_get_user_by_id_tests() {
    RUN_TEST(get_user_by_id_user_exists_returns_ok);
    RUN_TEST(get_user_by_id_user_does_not_exist_returns_not_found);
    RUN_TEST(get_user_by_id_error_ocourred_return_error);
}