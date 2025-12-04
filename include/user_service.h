#ifndef USER_SERVICE_H
#define USER_SERVICE_H

int get_users_service(AppContext *app, UserListDto *target);

int get_user_by_id_service(AppContext *app, UserDto *target, int id);

int create_user_service(AppContext *app, UserDto *user_dto);

int update_user_service(AppContext *app, UserDto *user_dto);

int delete_user_service(AppContext *app, int id);

#endif