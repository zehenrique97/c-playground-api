#include "app_context.h"
#include "user_entity.h"

#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

int user_repository_get_users(AppContext *app, UserEntity **users, int *count);
int user_repository_get_user_by_id(AppContext *app, UserEntity *target, int id);
int user_repository_create_user(AppContext *app, UserEntity *user);
int user_repository_update_user(AppContext *app, UserEntity *user);
int user_repository_delete_user(AppContext *app, int id);

#endif