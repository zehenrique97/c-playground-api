#include <stdlib.h>
#include <stdbool.h>
#include "unity.h"
#include "user.h"
#include "get_users_tests.h"
#include "user_repo_port_mock.h"
#include "user_repo_port.h"
#include "get_users_uc.h"

void get_users_users_exists_returns_ok() {
    User *user_list;
    int count = 0;
    UserRepoPortMock *mock = calloc(1, sizeof(UserRepoPortMock));
    mock->get_users_calls = 0;
    mock->returned_user_list[0] = (User) {
        .id = 1,
        .name = "Jose",
        .age = 20
    };
    mock->returned_user_list[1] = (User) {
        .id = 2,
        .name = "Maria",
        .age = 22
    };
    mock->returned_user_list[2] = (User) {
        .id = 3,
        .name = "Joao",
        .age = 30
    };
    UserRepoPort repo = {.ctx = mock, .get_users = get_users_mock};
    GetUsersUc get_users_uc = {.repo = repo};

    UserUcStatus rc = get_users_uc_handle(&get_users_uc, &user_list, &count);

    TEST_ASSERT_EQUAL_INT(USER_UC_SUCCESS, rc);
    for(int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL_INT(mock->returned_user_list[i].id, user_list[i].id);
        TEST_ASSERT_EQUAL_CHAR_ARRAY(mock->returned_user_list[i].name,user_list[i].name, sizeof(mock->returned_user_list[i].name));
        TEST_ASSERT_EQUAL_INT(mock->returned_user_list[i].age, user_list[i].age);
    }
    TEST_ASSERT_EQUAL_INT(3, count);
    TEST_ASSERT_EQUAL_INT(1, mock->get_users_calls);
}

void get_users_users_dont_exist_returns_not_found() {
    User *user_list;
    int count = 0;
    UserRepoPortMock mock = {.get_users_calls = 0, .should_be_not_found = true};
    UserRepoPort repo = {.ctx = &mock, .get_users = get_users_mock};
    GetUsersUc get_users_uc = {.repo = repo};

    UserUcStatus rc = get_users_uc_handle(&get_users_uc, &user_list, &count);

    TEST_ASSERT_EQUAL_INT(USER_UC_NOT_FOUND, rc);
    TEST_ASSERT_EQUAL_INT(0, count);
    TEST_ASSERT_EQUAL_INT(1, mock.get_users_calls);
}

void get_users_error_occurred_return_error() {
    User *user_list;
    int count = 0;
    UserRepoPortMock mock = {.get_users_calls = 0, .should_throw_error = true};
    UserRepoPort repo = {.ctx = &mock, .get_users = get_users_mock};
    GetUsersUc get_users_uc = {.repo = repo};

    UserUcStatus rc = get_users_uc_handle(&get_users_uc, &user_list, &count);

    TEST_ASSERT_EQUAL_INT(USER_UC_ERROR, rc);
    TEST_ASSERT_EQUAL_INT(0, count);
    TEST_ASSERT_EQUAL_INT(1, mock.get_users_calls);
}

void run_get_users_tests() {
    RUN_TEST(get_users_users_exists_returns_ok);
    RUN_TEST(get_users_users_dont_exist_returns_not_found);
    RUN_TEST(get_users_error_occurred_return_error);
}