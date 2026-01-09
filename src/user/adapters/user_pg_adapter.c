#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"
#include "user_pg_adapter.h"
#include "user_repo_port.h"

static void user_copy_name(char *dest, size_t dest_size, const char *src) {
    if (dest == NULL || dest_size == 0) return;
    if (src == NULL) {
        dest[0] = '\0';
        return;
    }
    snprintf(dest, dest_size, "%s", src);
}

UserRepoStatus user_pg_adapter_get_users(void *ctx, User **users, int *count) {
    UserPgAdapter *user_pg_adapter = (UserPgAdapter *) ctx;
    if (user_pg_adapter == NULL || user_pg_adapter->pool == NULL || users == NULL || count == NULL)
        return USER_REPO_ERROR;

    *users = NULL;
    *count = 0;

    PGconn *conn = pg_pool_acquire(user_pg_adapter->pool);
    if (conn == NULL) return USER_REPO_ERROR;

    PGresult *result = PQexec(conn, "SELECT * FROM users;");
    if(PQresultStatus(result) != PGRES_TUPLES_OK) {
        PQclear(result);
        pg_pool_release(user_pg_adapter->pool, conn);
        return USER_REPO_ERROR;
    }

    int num_rows = PQntuples(result);
    if(num_rows == 0) {
        PQclear(result);
        pg_pool_release(user_pg_adapter->pool, conn);
        return USER_REPO_NOT_FOUND;
    }

    User *user_rows = malloc(num_rows * sizeof(User));
    if(user_rows == NULL) {
        PQclear(result);
        pg_pool_release(user_pg_adapter->pool, conn);
        return USER_REPO_ERROR;
    }

    for (int i = 0; i < num_rows; i++) {
        user_rows[i].id = atoi(PQgetvalue(result, i, 0));
        user_copy_name(user_rows[i].name, sizeof(user_rows[i].name), PQgetvalue(result, i, 1));
        user_rows[i].age = atoi(PQgetvalue(result, i, 2));
    }

    *users = user_rows;
    *count = num_rows;
    PQclear(result);
    pg_pool_release(user_pg_adapter->pool, conn);
    return USER_REPO_SUCCESS;
}

UserRepoStatus user_pg_adapter_get_user_by_id(void *ctx, int id, User *user) {
    UserPgAdapter *user_pg_adapter = (UserPgAdapter *) ctx;
    if (user_pg_adapter == NULL || user_pg_adapter->pool == NULL || user == NULL)
        return USER_REPO_ERROR;

    PGconn *conn = pg_pool_acquire(user_pg_adapter->pool);
    if (conn == NULL) return USER_REPO_ERROR;

    char buffer[255];
    snprintf(buffer, sizeof(buffer), "SELECT * FROM users WHERE id=%d;", id);

    PGresult *result = PQexec(conn, buffer);
    if (result == NULL) {
        pg_pool_release(user_pg_adapter->pool, conn);
        return USER_REPO_ERROR;
    }

    if(PQresultStatus(result) == PGRES_TUPLES_OK) {
        if(PQntuples(result) == 0) {
            PQclear(result);
            pg_pool_release(user_pg_adapter->pool, conn);
            return USER_REPO_NOT_FOUND;
        }

        user->id = atoi(PQgetvalue(result, 0, 0));
        user_copy_name(user->name, sizeof(user->name), PQgetvalue(result, 0, 1));
        user->age = atoi(PQgetvalue(result, 0, 2));

        PQclear(result);
        pg_pool_release(user_pg_adapter->pool, conn);
        return USER_REPO_SUCCESS;
    }

    PQclear(result);
    pg_pool_release(user_pg_adapter->pool, conn);
    return USER_REPO_ERROR;
}

UserRepoStatus user_pg_adapter_save_user(void *ctx, User *user) {
    UserPgAdapter *user_pg_adapter = (UserPgAdapter *) ctx;
    if (user_pg_adapter == NULL || user_pg_adapter->pool == NULL || user == NULL)
        return USER_REPO_ERROR;

    PGconn *conn = pg_pool_acquire(user_pg_adapter->pool);
    if (conn == NULL) return USER_REPO_ERROR;

    char buffer[255];
    snprintf(buffer, sizeof(buffer), "INSERT INTO users(name, age) VALUES('%s', %d);", user->name, user->age);

    PGresult *result = PQexec(conn, buffer);

    if(PQresultStatus(result) == PGRES_COMMAND_OK) {
        PQclear(result);
        pg_pool_release(user_pg_adapter->pool, conn);
        return USER_REPO_SUCCESS;
    }

    PQclear(result);
    pg_pool_release(user_pg_adapter->pool, conn);
    return USER_REPO_ERROR;
}

UserRepoStatus user_pg_adapter_update_user(void *ctx, User *user) {
    UserPgAdapter *user_pg_adapter = (UserPgAdapter *) ctx;
    if (user_pg_adapter == NULL || user_pg_adapter->pool == NULL || user == NULL)
        return USER_REPO_ERROR;

    UserRepoStatus rc = user_pg_adapter_get_user_by_id(ctx, user->id, user);
    if(rc == USER_REPO_NOT_FOUND) return rc;

    PGconn *conn = pg_pool_acquire(user_pg_adapter->pool);
    if (conn == NULL) return USER_REPO_ERROR;

    char buffer[255];
    snprintf(buffer, sizeof(buffer), "UPDATE users SET name='%s', age=%d WHERE id=%d;", user->name, user->age, user->id);

    PGresult *result = PQexec(conn, buffer);

    if(PQresultStatus(result) == PGRES_COMMAND_OK) {
        PQclear(result);
        pg_pool_release(user_pg_adapter->pool, conn);
        return USER_REPO_SUCCESS;
    }

    PQclear(result);
    pg_pool_release(user_pg_adapter->pool, conn);
    return USER_REPO_ERROR;
}

UserRepoStatus user_pg_adapter_delete_user(void *ctx, int id) {
    UserPgAdapter *user_pg_adapter = (UserPgAdapter *) ctx;
    if (user_pg_adapter == NULL || user_pg_adapter->pool == NULL)
        return USER_REPO_ERROR;

    User *user = calloc(1, sizeof(User));

    UserRepoStatus rc = user_pg_adapter_get_user_by_id(ctx, id, user);
    if(rc != USER_REPO_SUCCESS) {
        free(user);
        return rc;
    }

    PGconn *conn = pg_pool_acquire(user_pg_adapter->pool);
    if (conn == NULL) {
        free(user);
        return USER_REPO_ERROR;
    }

    char buffer[255];
    snprintf(buffer, sizeof(buffer), "DELETE FROM users WHERE id=%d;", id);

    PGresult *result = PQexec(conn, buffer);

    if(PQresultStatus(result) == PGRES_COMMAND_OK) {
        PQclear(result);
        pg_pool_release(user_pg_adapter->pool, conn);
        free(user);
        return USER_REPO_SUCCESS;
    }

    PQclear(result);
    pg_pool_release(user_pg_adapter->pool, conn);
    free(user);
    return USER_REPO_ERROR;
}
