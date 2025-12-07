#include "sql.h"
#include "mysql.h"
#include "sql_commands.h"
#include <stddef.h>
#include <stdio.h>

// returns connection ptr on success, and null on fail
extern MYSQL *
sql_connect (Context *ctx, char const *user, char const *password)
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
  ctx->conn = conn;
  return conn;
}

extern void
sql_disconnect (MYSQL *conn)
{
  mysql_close (conn);
}

extern int
sql_init (MYSQL *conn)
{
  for (int i = 0; i < sql_com_init_len; i++)
    {
      int code = mysql_query (conn, sql_com_init[i]);
      if (code)
        {
          printf ("FATAL ERROR: init command [%d/%d] failed, error: '%s'\n",
                  i + 1, sql_com_init_len, mysql_error (conn));
          return -1;
        }
      else
        {
          printf ("LOG: init command [%d/%d] succeded\n", i + 1,
                  sql_com_init_len);
        }
    }

  return 0;
}

extern int
sql_destroy (MYSQL *conn)
{
  char const *command = "DROP DATABASE IF EXISTS college_manager";
  int code = mysql_query (conn, command);
  if (code)
    {
      printf ("FATAL ERROR: could not drop database, error: '%s'\n",
              mysql_error (conn));
      return -1;
    }
  else
    {
      printf ("LOG: database dropping succeded\n");
    }

  return 0;
}
