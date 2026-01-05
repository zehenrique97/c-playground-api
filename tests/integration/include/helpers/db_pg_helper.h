#ifndef DB_PG_HELPER_H
#define DB_PG_HELPER_H

#include <libpq-fe.h>

int db_pg_init(PGconn **conn);
int db_pg_create_table(PGconn *conn, char *schema);
int db_pg_insert(PGconn *conn, char *table, char *parameters);
int db_pg_shutdown(PGconn *conn);

#endif