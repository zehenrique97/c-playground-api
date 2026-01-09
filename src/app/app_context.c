#include <stdio.h>
#include "app_context.h"

#define CONN_STRING "user=teste dbname=testedb password=teste123 host=localhost"
#define DB_POOL_SIZE 10

int app_init(AppContext *app) {
    printf("Connecting to DB on localhost:5432...\n");
    if (pg_pool_init(&app->pool, CONN_STRING, DB_POOL_SIZE) == 0) {
        printf("Connection pool established (size=%d)\n", DB_POOL_SIZE);
        app->user_pg_adapter = (UserPgAdapter){ .pool = &app->pool };

        app->user_repo_port = (UserRepoPort){
            .ctx = &app->user_pg_adapter,
            .get_users = user_pg_adapter_get_users,
            .get_user_by_id = user_pg_adapter_get_user_by_id,
            .save_user = user_pg_adapter_save_user,
            .update_user = user_pg_adapter_update_user,
            .delete_user = user_pg_adapter_delete_user
        };

        app->get_users_uc = (GetUsersUc){ .repo = app->user_repo_port };
        app->get_user_by_id_uc = (GetUserByIdUc){ .repo = app->user_repo_port };
        app->create_user_uc = (CreateUserUc){ .repo = app->user_repo_port };
        app->update_user_uc = (UpdateUserUc){ .repo = app->user_repo_port };
        app->delete_user_uc = (DeleteUserUc){ .repo = app->user_repo_port };

        app->get_users_port = (GetUsersPort){
            .ctx = &app->get_users_uc,
            .handle = get_users_uc_handle
        };
        app->get_user_port_by_id = (GetUserByIdPort){
            .ctx = &app->get_user_by_id_uc,
            .handle = get_user_by_id_uc_handle
        };
        app->create_user_port = (CreateUserPort){
            .ctx = &app->create_user_uc,
            .handle = create_user_uc_handle
        };
        app->update_user_port = (UpdateUserPort){
            .ctx = &app->update_user_uc,
            .handle = update_user_uc_handle
        };
        app->delete_user_port = (DeleteUserPort){
            .ctx = &app->delete_user_uc,
            .handle = delete_user_uc_handle
        };

        return 0;
    }

    fprintf(stderr, "Could not establish connection pool with database\n");
    return 1;
}

void app_shutdown(AppContext *app) {
    pg_pool_shutdown(&app->pool);
}
