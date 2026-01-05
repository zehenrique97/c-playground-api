#include <libpq-fe.h>
#include <stdio.h>
#include "user_pg_adapter_tests.h"
#include "user_pg_adapter.h"
#include "user_repo_port.h"

void get_user_by_id_user_exists_return_user() {
    User user;
    UserPgAdapter adapter = {.conn = conn};
    UserRepoStatus rc = user_pg_adapter_get_user_by_id(&adapter, 1, &user);
    (void)rc;

    printf("%d, %s, %d\n", user.id, user.name, user.age);
}

void run_user_pg_adapter_get_user_by_id_tests() {
    get_user_by_id_user_exists_return_user();
}
