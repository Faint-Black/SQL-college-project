#include "sql.h"
#include "sql_commands.h"
#include <stddef.h>
#include <stdio.h>

#if defined(USE_MARIADB)
#include <mariadb/mysql.h>
#elif defined(USE_MYSQL)
#include <mysql.h>
#else
#error "no DB API found"
#endif

// returns connection ptr on success, and null on fail
static MYSQL *
sql_connect (char const *user, char const *password)
{
  MYSQL *conn;
  // init connection object
  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      return NULL;
    }
  // apply connection to daemon
  if (mysql_real_connect (conn, "localhost", user, password, NULL, 0, NULL, 0)
      == NULL)
    {
      mysql_close (conn);
      return NULL;
    }
  return conn;
}

extern int
sql_init (void)
{
  MYSQL *conn = sql_connect (DB_USR, DB_PWD);
  if (conn == NULL)
    {
      printf ("FATAL ERROR: sql_connect() failed\n");
      return -1;
    }

  // execute commands
  for (int i = 0; i < sql_com_init_len; i++)
    {
      int code = mysql_query (conn, sql_com_init[i]);
      if (code)
        {
          printf ("FATAL ERROR: init command [%d/%d] failed, error: '%s'\n",
                  i + 1, sql_com_init_len, mysql_error (conn));
          mysql_close (conn);
          return 0;
        }
      else
        {
          printf ("LOG: init command [%d/%d] succeded\n", i + 1,
                  sql_com_init_len);
        }
    }

  mysql_close (conn);
  return 0;
}

extern int
sql_destroy (void)
{
  MYSQL *conn = sql_connect (DB_USR, DB_PWD);
  if (conn == NULL)
    {
      printf ("FATAL ERROR: sql_connect() failed\n");
      return -1;
    }

  // execute commands
  char const *command = "DROP DATABASE IF EXISTS college_manager";
  int code = mysql_query (conn, command);
  if (code)
    {
      printf ("FATAL ERROR: could not drop database, error: '%s'\n",
              mysql_error (conn));
      mysql_close (conn);
      return 0;
    }
  else
    {
      printf ("LOG: database dropping succeded\n");
    }

  mysql_close (conn);
  return 0;
}
