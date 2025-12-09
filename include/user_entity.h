#ifndef USER_ENTITY_H
#define USER_ENTITY_H

typedef struct {
    int id;
    char *name;
    int age;
} User;

User *user_create(void);
void user_destroy(User *user);

void query_to_user(User *user, PGresult *result, int row_number);

#endif