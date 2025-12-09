#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

int user_controller_get_users(const struct _u_request *req, struct _u_response *res, void *user_data);
int user_controller_get_user_by_id(const struct _u_request *req, struct _u_response *res, void *user_data);
int user_controller_post_user(const struct _u_request *req, struct _u_response *res, void *user_data);
int user_controller_put_user(const struct _u_request *req, struct _u_response *res, void *user_data);
int user_controller_delete_user(const struct _u_request *req, struct _u_response *res, void *user_data);

#endif