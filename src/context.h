#pragma once

#if defined(USE_MARIADB)
#include <mariadb/mysql.h>
#elif defined(USE_MYSQL)
#include <mysql.h>
#else
#error "no DB API found"
#endif

// non-owning collection of global-state variables
typedef struct Context
{
  MYSQL *conn;
  struct LogWidgets *log;
} Context;

extern Context *context_init (void);
extern void context_deinit (Context *ctx);
