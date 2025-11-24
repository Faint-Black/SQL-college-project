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

  // TODO: remove this
  mysql_close (conn);
  return 0;
}
