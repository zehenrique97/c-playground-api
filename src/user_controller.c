#include <stdlib.h>
#include <ulfius.h>
#include <jansson.h>
#include "../include/app_context.h"
#include "../include/user_controller.h"
#include "../include/user_dto.h"
#include "../include/user_service.h"

int get_users(const struct _u_request *req, struct _u_response *res, void *user_data) {
    AppContext *app = (AppContext *) user_data;
    UserListDto user_list_dto;

    int status = get_users_service(app, &user_list_dto);

    if(status == 1)
        ulfius_set_json_body_response(res, 500, NULL);
    else if(status == 2)
        ulfius_set_empty_body_response(res, 204);
    else {
        json_t *payload;
        map_user_dto_to_json_array(&user_list_dto, &payload);
        ulfius_set_json_body_response(res, 200, payload);
    }

    return U_CALLBACK_COMPLETE;
}

int get_user_by_id(const struct _u_request *req, struct _u_response *res, void *user_data) {
    AppContext *app = (AppContext *) user_data;
    UserDto user_dto;

    char *id = u_map_get(req->map_url, "id");
    int status = get_user_by_id_service(app, &user_dto, atoi(id));

    if(status == 1)
        ulfius_set_json_body_response(res, 500, NULL);
    else if(status == 2)
        ulfius_set_empty_body_response(res, 204);
    else {
        json_t *payload;
        map_user_dto_to_json(&user_dto, &payload);
        ulfius_set_json_body_response(res, 200, payload);
    }

    return U_CALLBACK_COMPLETE;
}

int post_user(const struct _u_request *req, struct _u_response *res, void *user_data) {
    AppContext *app = (AppContext *) user_data;

    json_error_t json_error;
    json_t *body = ulfius_get_json_body_request(req, &json_error);

    json_t *j_name = json_object_get(body, "name");
    json_t *j_age = json_object_get(body, "age");

    // TODO: adicionar um validator aqui

    char *name = json_string_value(j_name);
    int age = (int) json_integer_value(j_age);

    UserDto user_dto = {
        .id = 0,
        .name = name,
        .age = age
    };

    int status = create_user_service(app, &user_dto);

    json_decref(body);

    if(status == 1)
        ulfius_set_json_body_response(res, 500, NULL);
    else
        ulfius_set_empty_body_response(res, 201);

    return U_CALLBACK_COMPLETE;
}

int put_user(const struct _u_request *req, struct _u_response *res, void *user_data) {
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

    UserDto user_dto = {
        .id = id,
        .name = name,
        .age = age
    };

    int status = update_user_service(app, &user_dto);

    // TODO: Mapear os status para um enum
    if(status == 1)
        ulfius_set_json_body_response(res, 500, NULL);
    else
        ulfius_set_empty_body_response(res, 200);

    json_decref(body);
    
    return U_CALLBACK_COMPLETE;
}

int delete_user(const struct _u_request *req, struct _u_response *res, void *user_data) {
    AppContext *app = (AppContext *) user_data;
    char *id = u_map_get(req->map_url, "id");

    int status = delete_user_service(app, atoi(id));

    if(status == 1)
        ulfius_set_json_body_response(res, 500, NULL);
    else
        ulfius_set_empty_body_response(res, 200);
    
    return U_CALLBACK_COMPLETE;
}