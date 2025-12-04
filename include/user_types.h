#ifndef USER_TYPES_H
#define USER_TYPES_H

typedef struct {
    int id;
    char *name;
    int age;
} UserDto;

typedef struct {
    int number_of_users;
    UserDto *user_dto_list;
} UserListDto;

typedef struct {
    int id;
    char *name;
    int age;
} UserEntity;

#endif