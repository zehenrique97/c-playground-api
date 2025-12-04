#include <libpq-fe.h>

#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

typedef struct {
    PGconn *db;
} AppContext;

int app_init(AppContext *app);

void app_shutdown(AppContext *app);

#endif