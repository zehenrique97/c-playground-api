#include <libpq-fe.h>
#include <stdlib.h>
#include "unity.h"
#include "user.h"
#include "user_pg_adapter_save_user_tests.h"
#include "user_pg_adapter.h"
#include "user_repo_port.h"

void save_user_user_inserted_return_ok() {
    User *user = calloc(1, sizeof(User));
    UserPgAdapter adapter = {.conn = conn};

    UserRepoStatus rc = user_pg_adapter_save_user(&adapter, user);

    TEST_ASSERT_EQUAL_INT(USER_REPO_SUCCESS, rc);
}

void run_user_pg_adapter_save_user_tests() {
    RUN_TEST(save_user_user_inserted_return_ok);
}