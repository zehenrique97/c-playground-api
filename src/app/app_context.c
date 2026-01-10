#include <stdio.h>
#include <stdlib.h>
#include "app_context.h"
#include "pg_pool.h"

int app_init(AppContext *app) {
    printf("Connecting to DB on localhost:5432...\n");
    app->pg_pool = malloc(sizeof(PgPool *));

    int pool_status = pg_pool_init(app->pg_pool, 5);

    if(pool_status == PG_POOL_SUCCESS) {
        app->user_pg_adapter = (UserPgAdapter){ .pg_pool = app->pg_pool };

        app->user_repo_port = (UserRepoPort) {
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

    return 1;
}

void app_shutdown(AppContext *app) {
    pg_pool_destroy(app->pg_pool);
    free(app->pg_pool);
}
