#include "unity.h"
#include "get_users_tests.h"
#include "get_user_by_id_tests.h"
#include "create_user_tests.h"
#include "update_user_tests.h"
#include "delete_user_tests.h"

void setUp() {}

void tearDown() {}

int main() {
    UNITY_BEGIN();
    run_get_users_tests();
    run_get_user_by_id_tests();
    run_create_user_tests();
    run_update_user_tests();
    run_delete_user_tests();
    return UNITY_END();
}