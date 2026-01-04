#include "unity.h"
#include "get_users_tests.h"
#include "get_user_by_id_tests.h"

void setUp() {}

void tearDown() {}

int main() {
    UNITY_BEGIN();
    run_get_users_tests();
    run_get_user_by_id_tests();
    return UNITY_END();
}