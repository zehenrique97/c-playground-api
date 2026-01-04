#include <stdlib.h>
#include <ulfius.h>
#include <jansson.h>
#include <string.h>
#include "user_controller_adapter.h"
#include "user.h"
#include "get_users_port.h"
#include "get_user_by_id_port.h"
#include "create_user_port.h"
#include "update_user_port.h"
#include "delete_user_port.h"
#include "user_uc_status.h"

int user_controller_adapter_get_users(const struct _u_request *req, struct _u_response *res, void *user_data) {
    GetUsersPort *get_users_port = (GetUsersPort *) user_data;
    User *user_list;
    int number_of_users = 0;

    UserUcStatus rc = get_users_port->handle(get_users_port->ctx, &user_list, &number_of_users);

    if(rc == USER_UC_ERROR)
        ulfius_set_json_body_response(res, 500, NULL);
    else if(rc == USER_UC_NOT_FOUND)
        ulfius_set_empty_body_response(res, 204);
    else {
        json_t *root = json_object();
        json_t *user_array = json_array();

        for(int i = 0; i < number_of_users; i++) {
            json_t *user_as_json = json_pack("{s:i,s:s,s:i}", "id", user_list[i].id, "name", user_list[i].name, "age", user_list[i].age);
            json_array_append_new(user_array, user_as_json);
        }

        json_object_set_new(root, "count", json_integer(number_of_users));
        json_object_set_new(root, "users", user_array);

        ulfius_set_json_body_response(res, 200, root);
    }

    free(user_list);

    return U_CALLBACK_COMPLETE;
}

int user_controller_adapter_get_user_by_id(const struct _u_request *req, struct _u_response *res, void *user_data) {
    GetUserByIdPort *get_user_by_id_port = (GetUserByIdPort *) user_data;
    User *user = malloc(sizeof(User));

    const char *id = u_map_get(req->map_url, "id");

    UserUcStatus rc = get_user_by_id_port->handle(get_user_by_id_port->ctx, atoi(id), user);

    if(rc == USER_UC_ERROR)
        ulfius_set_json_body_response(res, 500, NULL);
    else if(rc == USER_UC_NOT_FOUND)
        ulfius_set_empty_body_response(res, 204);
    else {
        json_t *payload = json_pack("{s:i,s:s,s:i}", "id", user->id, "name", user->name, "age", user->age);
        ulfius_set_json_body_response(res, 200, payload);
    }

    free(user);

    return U_CALLBACK_COMPLETE;
}

int user_controller_adapter_post_user(const struct _u_request *req, struct _u_response *res, void *user_data) {
    CreateUserPort *create_user_port = (CreateUserPort *) user_data;

    json_error_t json_error;
    json_t *body = ulfius_get_json_body_request(req, &json_error);

    json_t *j_name = json_object_get(body, "name");
    json_t *j_age = json_object_get(body, "age");

    const char *name = json_string_value(j_name);
    int age = (int) json_integer_value(j_age);

    User *user = malloc(sizeof(User));
    
    user->id = 0;
    strcpy(user->name, name);
    user->age = age;

    UserUcStatus rc = create_user_port->handle(create_user_port->ctx, user);

    json_decref(body);

    if(rc == USER_UC_ERROR)
        ulfius_set_json_body_response(res, 500, NULL);
    else
        ulfius_set_empty_body_response(res, 201);


    free(user);
    return U_CALLBACK_COMPLETE;
}

int user_controller_adapter_put_user(const struct _u_request *req, struct _u_response *res, void *user_data) {
    UpdateUserPort *update_user_port = (UpdateUserPort *) user_data;

    json_error_t json_error;
    json_t *body = ulfius_get_json_body_request(req, &json_error);
    json_t *j_id = json_object_get(body, "id");
    json_t *j_name = json_object_get(body, "name");
    json_t *j_age = json_object_get(body, "age");

    int id = (int) json_integer_value(j_id);
    const char *name = json_string_value(j_name);
    int age = (int) json_integer_value(j_age);

    User *user = malloc(sizeof(User));
    
    user->id = id;
    strcpy(user->name, name);
    user->age = age;

    UserUcStatus rc = update_user_port->handle(update_user_port->ctx, user);

    if(rc == USER_UC_ERROR)
        ulfius_set_json_body_response(res, 500, NULL);
    else
        ulfius_set_empty_body_response(res, 200);

    free(user);
    json_decref(body);
    
    return U_CALLBACK_COMPLETE;
}

int user_controller_adapter_delete_user(const struct _u_request *req, struct _u_response *res, void *user_data) {
    DeleteUserPort *delete_user_port = (DeleteUserPort *) user_data;
    const char *id = u_map_get(req->map_url, "id");

    UserUcStatus rc = delete_user_port->handle(delete_user_port->ctx, atoi(id));

    if(rc == USER_UC_ERROR)
        ulfius_set_json_body_response(res, 500, NULL);
    else
        ulfius_set_empty_body_response(res, 200);
    
    return U_CALLBACK_COMPLETE;
}
