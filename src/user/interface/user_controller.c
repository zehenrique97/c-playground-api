#include <stdlib.h>
#include <ulfius.h>
#include <jansson.h>
#include <string.h>
#include "app_context.h"
#include "user_controller.h"
#include "user_service.h"
#include "user_entity.h"

int user_controller_get_users(const struct _u_request *req, struct _u_response *res, void *user_data) {
    AppContext *app = (AppContext *) user_data;
    User *user_list = NULL;
    int number_of_users = 0;

    int status = user_service_get_users(app, &user_list, &number_of_users);

    if(status == 1)
        ulfius_set_json_body_response(res, 500, NULL);
    else if(status == 2)
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

int user_controller_get_user_by_id(const struct _u_request *req, struct _u_response *res, void *user_data) {
    AppContext *app = (AppContext *) user_data;
    User *user = user_create();

    char *id = u_map_get(req->map_url, "id");
    user->id = atoi(id);
    int status = user_service_get_user_by_id(app, user);

    if(status == 1)
        ulfius_set_json_body_response(res, 500, NULL);
    else if(status == 2)
        ulfius_set_empty_body_response(res, 204);
    else {
        json_t *payload = json_pack("{s:i,s:s,s:i}", "id", user->id, "name", user->name, "age", user->age);
        ulfius_set_json_body_response(res, 200, payload);
    }

    user_destroy(user);

    return U_CALLBACK_COMPLETE;
}

int user_controller_post_user(const struct _u_request *req, struct _u_response *res, void *user_data) {
    AppContext *app = (AppContext *) user_data;

    json_error_t json_error;
    json_t *body = ulfius_get_json_body_request(req, &json_error);

    json_t *j_name = json_object_get(body, "name");
    json_t *j_age = json_object_get(body, "age");

    // TODO: adicionar um validator aqui

    char *name = json_string_value(j_name);
    int age = (int) json_integer_value(j_age);

    User *user = user_create();
    
    user->id = 0;
    strcpy(user->name, name);
    user->age = age;

    int status = user_service_create_user(app, user);

    user_destroy(user);
    json_decref(body);

    if(status == 1)
        ulfius_set_json_body_response(res, 500, NULL);
    else
        ulfius_set_empty_body_response(res, 201);

    return U_CALLBACK_COMPLETE;
}

int user_controller_put_user(const struct _u_request *req, struct _u_response *res, void *user_data) {
    AppContext *app = (AppContext *) user_data;

    // TODO: Implementar uma função para a conversão de json body->DTO
    json_error_t json_error;
    json_t *body = ulfius_get_json_body_request(req, &json_error);
    json_t *j_id = json_object_get(body, "id");
    json_t *j_name = json_object_get(body, "name");
    json_t *j_age = json_object_get(body, "age");

    int id = (int) json_integer_value(j_id);
    char *name = json_string_value(j_name);
    int age = (int) json_integer_value(j_age);

    User *user = user_create();
    
    user->id = id;
    strcpy(user->name, name);
    user->age = age;

    int status = user_service_update_user(app, user);

    // TODO: Mapear os status para um enum
    if(status == 1)
        ulfius_set_json_body_response(res, 500, NULL);
    else
        ulfius_set_empty_body_response(res, 200);

    user_destroy(user);
    json_decref(body);
    
    return U_CALLBACK_COMPLETE;
}

int user_controller_delete_user(const struct _u_request *req, struct _u_response *res, void *user_data) {
    AppContext *app = (AppContext *) user_data;
    char *id = u_map_get(req->map_url, "id");

    int status = user_service_delete_user(app, atoi(id));

    if(status == 1)
        ulfius_set_json_body_response(res, 500, NULL);
    else
        ulfius_set_empty_body_response(res, 200);
    
    return U_CALLBACK_COMPLETE;
}
