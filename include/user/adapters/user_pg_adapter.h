#ifndef USER_PG_ADAPTER_H
#define USER_PG_ADAPTER_H

#include <libpq-fe.h>

typedef struct UserPgAdapter {
    PGconn *conn;
} UserPgAdapter;

int user_pg_adapter_get_users(void *ctx, User **users, int *count);
int user_pg_adapter_get_user_by_id(void *ctx, int id, User *user);
int user_pg_adapter_save_user(void *ctx, User *user);
int user_pg_adapter_update_user(void *ctx, User *user);
int user_pg_adapter_delete_user(void *ctx, int id);

#endif
