#pragma once
#include "context.h"

#if defined(USE_MARIADB)
#include <mariadb/mysql.h>
#elif defined(USE_MYSQL)
#include <mysql.h>
#else
#error "no DB API found"
#endif

// Establish database connection
extern MYSQL *sql_connect (Context *ctx, char const *user,
                           char const *password);
// Close database connection
extern void sql_disconnect (MYSQL *conn);
// Creates the database and sets up the tables
extern int sql_init (MYSQL *conn);
// Drops the database
extern int sql_destroy (MYSQL *conn);
