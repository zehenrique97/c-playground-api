#ifndef USER_ENTITY_H
#define USER_ENTITY_H

typedef struct {
    int id;
    char name[255];
    int age;
} User;

User *user_create(void);
void user_destroy(User *user);

#endif