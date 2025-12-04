#include <jansson.h>
#include <stdio.h>
#include "../include/user_dto.h"

#define OBJECT_STRING "{s:i,s:s,s:i}"

int map_user_json_to_dto(json_t *root, UserDto *dto) {
    int id;
    const char *name;
    int age;

    if(json_unpack(root, OBJECT_STRING, "id", &id, "name", &name, "age", &age) != 0)
        return 1;

    dto->id = id;
    dto->name = name;
    dto->age = age;

    return 0;
}

int map_user_dto_to_json(UserDto *dto, json_t **target) {
    *target = json_pack(OBJECT_STRING, "id", dto->id, "name", dto->name, "age", dto->age);

    if(*target == NULL)
        return 1;

    return 0;
}

int map_user_dto_to_json_array(UserListDto *dto, json_t **target) {
    json_t *root = json_object();
    json_t *user_array = json_array();

    for(int i = 0; i < dto->number_of_users; i++) {
        UserDto user = dto->user_dto_list[i];
        json_t *user_as_json;
        map_user_dto_to_json(&user, &user_as_json);

        if(json_array_append_new(user_array, user_as_json) != 0) {
            json_decref(user_as_json);
            json_decref(user_array);
            json_decref(*target);
            return 1;
        }
    }

    json_object_set_new(root, "count", json_integer(dto->number_of_users));
    json_object_set_new(root, "users", user_array);

    *target = root;

    return 0;
}