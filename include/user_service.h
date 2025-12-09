#ifndef USER_SERVICE_H
#define USER_SERVICE_H

int user_service_get_users(AppContext *app, UserListDto *target);

int user_service_get_user_by_id(AppContext *app, UserDto *target, int id);

int user_service_create_user(AppContext *app, UserDto *user_dto);

int user_service_update_user(AppContext *app, UserDto *user_dto);

int user_service_delete_user(AppContext *app, int id);

#endif