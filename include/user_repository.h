#include "app_context.h"
#include "user_entity.h"

#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

int get_users_entity(AppContext *app, UserEntity **users, int *count);
int get_user_entity_by_id(AppContext *app, UserEntity *target, int id);
int create_user_entity(AppContext *app, UserEntity *user);
int update_user_entity(AppContext *app, UserEntity *user);
int delete_user_entity(AppContext *app, int id);

#endif