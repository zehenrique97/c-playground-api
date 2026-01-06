#include <libpq-fe.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "user_pg_adapter.h"
#include "user_repo_port.h"

UserRepoStatus user_pg_adapter_get_users(void *ctx, User **users, int *count) {
    UserPgAdapter *user_pg_adapter = (UserPgAdapter *) ctx;

    PGresult *result = PQexec(user_pg_adapter->conn, "SELECT * FROM users;");
    if(PQresultStatus(result) != PGRES_TUPLES_OK) {
        PQclear(result);
        return USER_REPO_ERROR;
    }

    int num_rows = PQntuples(result);
    if(num_rows == 0) {
        PQclear(result);
        *users = NULL;
        *count = 0;
        return USER_REPO_NOT_FOUND;
    }

    User *user_rows = malloc(num_rows * sizeof(User));
    if(user_rows == NULL) {
        PQclear(result);
        return USER_REPO_ERROR;
    }

    for (int i = 0; i < num_rows; i++) {
        user_rows[i].id = atoi(PQgetvalue(result, i, 0));
        strcpy(user_rows[i].name, PQgetvalue(result, i, 1));
        user_rows[i].age = atoi(PQgetvalue(result, i, 2));
    }

    *users = user_rows;
    *count = num_rows;
    PQclear(result);
    return USER_REPO_SUCCESS;
}

UserRepoStatus user_pg_adapter_get_user_by_id(void *ctx, int id, User *user) {
    UserPgAdapter *user_pg_adapter = (UserPgAdapter *) ctx;

    char buffer[255];
    snprintf(buffer, sizeof(buffer), "SELECT * FROM users WHERE id=%d;", id);

    PGresult *result = PQexec(user_pg_adapter->conn, buffer);

    if(PQresultStatus(result) == PGRES_TUPLES_OK) {
        if(PQntuples(result) == 0) return USER_REPO_NOT_FOUND;

        user->id = atoi(PQgetvalue(result, 0, 0));
        strcpy(user->name, PQgetvalue(result, 0, 1));
        user->age = atoi(PQgetvalue(result, 0, 2));

        return USER_REPO_SUCCESS;
    }

    return USER_REPO_ERROR;
}

UserRepoStatus user_pg_adapter_save_user(void *ctx, User *user) {
    UserPgAdapter *user_pg_adapter = (UserPgAdapter *) ctx;

    char buffer[255];
    snprintf(buffer, sizeof(buffer), "INSERT INTO users(name, age) VALUES('%s', %d);", user->name, user->age);

    PGresult *result = PQexec(user_pg_adapter->conn, buffer);

    if(PQresultStatus(result) == PGRES_COMMAND_OK)
        return USER_REPO_SUCCESS;

    return USER_REPO_ERROR;
}

UserRepoStatus user_pg_adapter_update_user(void *ctx, User *user) {
    UserPgAdapter *user_pg_adapter = (UserPgAdapter *) ctx;

    UserRepoStatus rc = user_pg_adapter_get_user_by_id(ctx, user->id, user);
    if(rc == USER_REPO_NOT_FOUND) return rc;

    char buffer[255];
    snprintf(buffer, sizeof(buffer), "UPDATE users SET name='%s', age=%d WHERE id=%d;", user->name, user->age, user->id);

    PGresult *result = PQexec(user_pg_adapter->conn, buffer);

    if(PQresultStatus(result) == PGRES_COMMAND_OK)
        return USER_REPO_SUCCESS;

    return USER_REPO_ERROR;
}

UserRepoStatus user_pg_adapter_delete_user(void *ctx, int id) {
    UserPgAdapter *user_pg_adapter = (UserPgAdapter *) ctx;

    User *user = calloc(1, sizeof(User));

    UserRepoStatus rc = user_pg_adapter_get_user_by_id(ctx, id, user);
    if(rc == USER_REPO_NOT_FOUND) return rc;

    char buffer[255];
    snprintf(buffer, sizeof(buffer), "DELETE FROM users WHERE id=%d;", id);

    PGresult *result = PQexec(user_pg_adapter->conn, buffer);

    if(PQresultStatus(result) == PGRES_COMMAND_OK)
        return USER_REPO_SUCCESS;

    return USER_REPO_ERROR;
}
