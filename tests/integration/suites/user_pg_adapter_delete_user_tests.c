#include <libpq-fe.h>
#include <stdlib.h>
#include "unity.h"
#include "user.h"
#include "user_pg_adapter_delete_user_tests.h"
#include "user_pg_adapter.h"
#include "user_repo_port.h"

void delete_user_user_deleted_return_ok() {
    UserPgAdapter adapter = {.pg_pool = pg_pool};

    UserRepoStatus rc = user_pg_adapter_delete_user(&adapter, 1);

    TEST_ASSERT_EQUAL_INT(USER_REPO_SUCCESS, rc);
}

void delete_user_user_does_not_exist_return_not_found() {
    UserPgAdapter adapter = {.pg_pool = pg_pool};

    UserRepoStatus rc = user_pg_adapter_delete_user(&adapter, 4);

    TEST_ASSERT_EQUAL_INT(USER_REPO_NOT_FOUND, rc);
}

void run_user_pg_adapter_delete_user_tests() {
    RUN_TEST(delete_user_user_deleted_return_ok);
    RUN_TEST(delete_user_user_does_not_exist_return_not_found);
}