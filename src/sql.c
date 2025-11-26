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

extern int
sql_init (void)
{
  MYSQL *conn;

  // init connection object
  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      printf ("FATAL ERROR: mysql_init() failed\n");
      return -1;
    }
  else
    {
      printf ("LOG: mysql_init() succeeded\n");
    }

  // apply connection to daemon
  if (mysql_real_connect (conn, "localhost", DB_USR, DB_PWD, NULL, 0, NULL, 0)
      == NULL)
    {
      printf ("FATAL ERROR: mysql_real_connect() failed\n");
      mysql_close (conn);
      return -1;
    }
  else
    {
      printf ("LOG: mysql_real_connect() succeeded\n");
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

  // TODO: remove this
  mysql_close (conn);
  return 0;
}
