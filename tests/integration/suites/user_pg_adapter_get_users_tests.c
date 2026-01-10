#include <libpq-fe.h>
#include <stdlib.h>
#include "unity.h"
#include "user.h"
#include "user_pg_adapter_get_users_tests.h"
#include "user_pg_adapter.h"
#include "user_repo_port.h"
#include "db_pg_helper.h"

void get_users_users_exists_return_ok() {
    User *user_list;
    int count = 0;
    UserPgAdapter adapter = {.pg_pool = pg_pool};

    UserRepoStatus rc = user_pg_adapter_get_users(&adapter, &user_list, &count);

    TEST_ASSERT_EQUAL_INT(USER_REPO_SUCCESS, rc);
    TEST_ASSERT_EQUAL_INT(3, count);
}

void get_users_users_dont_exists_return_not_found() {
    User *user_list;
    int count = 0;
    UserPgAdapter adapter = {.pg_pool = pg_pool};

    db_pg_delete_all(conn, "users");
    UserRepoStatus rc = user_pg_adapter_get_users(&adapter, &user_list, &count);

    TEST_ASSERT_EQUAL_INT(USER_REPO_NOT_FOUND, rc);
    TEST_ASSERT_EQUAL_INT(0, count);
}

void run_user_pg_adapter_get_users_tests() {
    RUN_TEST(get_users_users_exists_return_ok);
    RUN_TEST(get_users_users_dont_exists_return_not_found);
}