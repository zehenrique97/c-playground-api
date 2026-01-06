#include <libpq-fe.h>
#include <stdlib.h>
#include "unity.h"
#include "user.h"
#include "user_pg_adapter_update_user_tests.h"
#include "user_pg_adapter.h"
#include "user_repo_port.h"

void update_user_user_updated_return_ok() {
    User expected_user = {.id = 1, .name = "User4", .age = 44};
    User *user = calloc(1, sizeof(User));
    UserPgAdapter adapter = {.conn = conn};

    UserRepoStatus rc = user_pg_adapter_update_user(&adapter, &expected_user);

    user_pg_adapter_get_user_by_id(&adapter, expected_user.id, user);

    TEST_ASSERT_EQUAL_INT(USER_REPO_SUCCESS, rc);
    TEST_ASSERT_EQUAL_INT(expected_user.id, user->id);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(expected_user.name, user->name, sizeof(expected_user.name));
    TEST_ASSERT_EQUAL_INT(expected_user.age, user->age);
}

void update_user_user_does_not_exist_return_not_found() {
    User expected_user = {.id = 4, .name = "User4", .age = 44};
    UserPgAdapter adapter = {.conn = conn};

    UserRepoStatus rc = user_pg_adapter_update_user(&adapter, &expected_user);

    TEST_ASSERT_EQUAL_INT(USER_REPO_NOT_FOUND, rc);
}

void run_user_pg_adapter_update_user_tests() {
    RUN_TEST(update_user_user_updated_return_ok);
    RUN_TEST(update_user_user_does_not_exist_return_not_found);
}