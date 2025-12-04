#include <jansson.h>
#include "user_types.h"

#ifndef USER_DTO_H
#define USER_DTO_H

int map_user_json_to_dto(json_t *root, UserDto *dto);

int map_user_dto_to_json(UserDto *dto, json_t **target);

int map_user_dto_to_json_array(UserListDto *dto, json_t **target);

#endif