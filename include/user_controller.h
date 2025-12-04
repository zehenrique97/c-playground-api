#ifndef USERS_CONTROLLERS_H
#define USERS_CONTROLLERS_H

int get_users(const struct _u_request *req, struct _u_response *res, void *user_data);
int get_user_by_id(const struct _u_request *req, struct _u_response *res, void *user_data);
int post_user(const struct _u_request *req, struct _u_response *res, void *user_data);
int put_user(const struct _u_request *req, struct _u_response *res, void *user_data);
int delete_user(const struct _u_request *req, struct _u_response *res, void *user_data);

#endif