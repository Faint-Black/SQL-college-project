#include "callbacks.h"
#include "context.h"
#include "sql.h"
#include "widgets.h"

extern void
callback_init_database (GtkWidget *widget, gpointer ctx)
{
  LogWidgets *log = ((Context *)ctx)->log;
  MYSQL *conn = ((Context *)ctx)->conn;
  if (sql_init (conn))
    append_log_error (log, "SQL could not initialize!");
  else
    append_log_notice (log, "SQL database fully initialized.");
}

extern void
callback_drop_database (GtkWidget *widget, gpointer ctx)
{
  LogWidgets *log = ((Context *)ctx)->log;
  MYSQL *conn = ((Context *)ctx)->conn;
  if (sql_destroy (conn))
    append_log_error (log, "SQL database could not be destroyed!");
  else
    append_log_notice (log, "SQL database dropped.");
}
