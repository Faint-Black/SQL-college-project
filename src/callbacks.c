#include "callbacks.h"
#include "sql.h"
#include "widgets.h"

extern void
callback_init_database (GtkWidget *widget, gpointer user_data)
{
  LogWidgets *log = (LogWidgets *)user_data;
  if (sql_init ())
    append_log_error (log, "SQL could not initialize!");
  else
    append_log_notice (log, "SQL database fully initialized.");
}

extern void
callback_drop_database (GtkWidget *widget, gpointer user_data)
{
  LogWidgets *log = (LogWidgets *)user_data;
  if (sql_destroy ())
    append_log_error (log, "SQL database could not be destroyed!");
  else
    append_log_notice (log, "SQL database dropped.");
}
