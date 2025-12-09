#include <jansson.h>

#ifndef USER_DTO_H
#define USER_DTO_H

typedef struct {
    int id;
    char *name;
    int age;
} UserDto;

typedef struct {
    int number_of_users;
    UserDto *user_dto_list;
} UserListDto;

int json_to_user(json_t *root, UserDto *dto);

int user_to_json(UserDto *dto, json_t **target);

int user_list_to_json_array(UserListDto *dto, json_t **target);

#endif