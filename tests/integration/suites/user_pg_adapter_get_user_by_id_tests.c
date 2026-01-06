#include <libpq-fe.h>
#include <stdlib.h>
#include "unity.h"
#include "user.h"
#include "user_pg_adapter_get_user_by_id_tests.h"
#include "user_pg_adapter.h"
#include "user_repo_port.h"

void get_user_by_id_user_exists_return_user() {
    User expected_user = {.id = 1, .name = "User1", .age = 20};
    User *user = calloc(1, sizeof(User));
    UserPgAdapter adapter = {.conn = conn};
    UserRepoStatus rc = user_pg_adapter_get_user_by_id(&adapter, expected_user.id, user);

    TEST_ASSERT_EQUAL_INT(USER_REPO_SUCCESS, rc);
    TEST_ASSERT_EQUAL_INT(expected_user.id, user->id);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(expected_user.name, user->name, sizeof(expected_user.name));
    TEST_ASSERT_EQUAL_INT(expected_user.age, user->age);
}

void run_user_pg_adapter_get_user_by_id_tests() {
    RUN_TEST(get_user_by_id_user_exists_return_user);
}
