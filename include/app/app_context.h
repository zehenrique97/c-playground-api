#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#include "pg_pool.h"
#include "get_users_port.h"
#include "get_user_by_id_port.h"
#include "create_user_port.h"
#include "update_user_port.h"
#include "delete_user_port.h"
#include "user_pg_adapter.h"
#include "user_repo_port.h"
#include "get_users_uc.h"
#include "get_user_by_id_uc.h"
#include "create_user_uc.h"
#include "update_user_uc.h"
#include "delete_user_uc.h"

typedef struct AppContext {
    PgPool pool;
    UserPgAdapter user_pg_adapter;
    UserRepoPort user_repo_port;
    GetUsersUc get_users_uc;
    GetUserByIdUc get_user_by_id_uc;
    CreateUserUc create_user_uc;
    UpdateUserUc update_user_uc;
    DeleteUserUc delete_user_uc;
    GetUsersPort get_users_port;
    GetUserByIdPort get_user_port_by_id;
    CreateUserPort create_user_port;
    UpdateUserPort update_user_port;
    DeleteUserPort delete_user_port;
} AppContext;

int app_init(AppContext *app);

void app_shutdown(AppContext *app);

#endif
