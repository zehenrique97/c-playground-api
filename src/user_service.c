#include <stdio.h>
#include <stdlib.h>
#include "../include/app_context.h"
#include "../include/user_repository.h"
#include "../include/user_types.h"

int get_users_service(AppContext *app, UserListDto *target) {
    UserEntity *user_entity_list;
    int num_users = 0;
    int status = get_users_entity(app, &user_entity_list, &num_users);

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

int get_user_by_id_service(AppContext *app, UserDto *target, int id) {
    UserEntity user_entity;
    int status = get_user_entity_by_id(app, &user_entity, id);

    if(status == 0) {
        target->id = user_entity.id;
        target->name = user_entity.name;
        target->age = user_entity.age;
    }

    return status;
}

int create_user_service(AppContext *app, UserDto *user_dto) {
    UserEntity user_entity = {
        .id = 0,
        .name = user_dto->name,
        .age = user_dto->age
    };

    int status = create_user_entity(app, &user_entity);

    return status;
}

int update_user_service(AppContext *app, UserDto *user_dto) {
    UserEntity user_entity = {
        .id = user_dto->id,
        .name = user_dto->name,
        .age = user_dto->age
    };

    int status = update_user_entity(app, &user_entity);

    return status;
}

int delete_user_service(AppContext *app, int id) {
    int status = delete_user_entity(app, id);
    
    return status;
}