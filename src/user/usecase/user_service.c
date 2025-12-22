#include "app_context.h"
#include "user_repository.h"
#include "user_entity.h"

int user_service_get_users(AppContext *app, User **user_list, int *number_of_users) {
    return user_repository_get_users(app, user_list, number_of_users);
}

int user_service_get_user_by_id(AppContext *app, User *user) {
    return user_repository_get_user_by_id(app, user);
}

int user_service_create_user(AppContext *app, User *user) {
    return user_repository_create_user(app, user);
}

int user_service_update_user(AppContext *app, User *user) {
    return user_repository_update_user(app, user);
}

int user_service_delete_user(AppContext *app, int id) {
    return user_repository_delete_user(app, id);
}
