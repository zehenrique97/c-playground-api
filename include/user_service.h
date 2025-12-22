#include "app_context.h"
#include "user_entity.h"

#ifndef USER_SERVICE_H
#define USER_SERVICE_H

int user_service_get_users(AppContext *app, User **user_list, int *number_of_users);

int user_service_get_user_by_id(AppContext *app, User *user);

int user_service_create_user(AppContext *app, User *user);

int user_service_update_user(AppContext *app, User *user);

int user_service_delete_user(AppContext *app, int id);

#endif
