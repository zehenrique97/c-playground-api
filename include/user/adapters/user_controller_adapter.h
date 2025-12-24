#ifndef USER_CONTROLLER_ADAPTER_H
#define USER_CONTROLLER_ADAPTER_H

#include <ulfius.h>

int user_controller_adapter_get_users(const struct _u_request *req, struct _u_response *res, void *user_data);
int user_controller_adapter_get_user_by_id(const struct _u_request *req, struct _u_response *res, void *user_data);
int user_controller_adapter_post_user(const struct _u_request *req, struct _u_response *res, void *user_data);
int user_controller_adapter_put_user(const struct _u_request *req, struct _u_response *res, void *user_data);
int user_controller_adapter_delete_user(const struct _u_request *req, struct _u_response *res, void *user_data);

#endif