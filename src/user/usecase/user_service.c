#include <stdio.h>
#include <stdlib.h>
#include "app_context.h"
#include "user_repository.h"
#include "user_types.h"

int user_service_get_users(AppContext *app, UserListDto *target) {
    UserEntity *user_entity_list;
    int num_users = 0;
    int status = user_repository_get_users(app, &user_entity_list, &num_users);

    UserDto *user_dto_list = malloc(num_users * sizeof(UserDto));

    for(int i = 0; i < num_users; i++) {
        UserDto user_dto_list_item = {
            .id = user_entity_list[i].id,
            .name = user_entity_list[i].name,
            .age = user_entity_list[i].age
        };

        user_dto_list[i] = user_dto_list_item;
    }

    target->user_dto_list = user_dto_list;
    target->number_of_users = num_users;
    return status;
}

int user_service_get_user_by_id(AppContext *app, UserDto *target, int id) {
    UserEntity user_entity;
    int status = user_repository_get_user_by_id(app, &user_entity, id);

    if(status == 0) {
        target->id = user_entity.id;
        target->name = user_entity.name;
        target->age = user_entity.age;
    }

    return status;
}

int user_service_create_user(AppContext *app, UserDto *user_dto) {
    UserEntity user_entity = {
        .id = 0,
        .name = user_dto->name,
        .age = user_dto->age
    };

    int status = user_repository_create_user(app, &user_entity);

    return status;
}

int user_service_update_user(AppContext *app, UserDto *user_dto) {
    UserEntity user_entity = {
        .id = user_dto->id,
        .name = user_dto->name,
        .age = user_dto->age
    };

    int status = user_repository_update_user(app, &user_entity);

    return status;
}

int user_service_delete_user(AppContext *app, int id) {
    int status = user_repository_delete_user(app, id);
    
    return status;
}