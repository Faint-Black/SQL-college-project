#include "callbacks.h"
#include "sql.h"

extern void
callback_init_database (GtkWidget *widget, gpointer user_data)
{
  if (sql_init ())
    {
      g_print ("FATAL ERROR: SQL could not initialize!\n");
      exit (EXIT_FAILURE);
    }
  else
    {
      g_print ("LOG: SQL database fully initialized\n");
    }
}

extern void
callback_drop_database (GtkWidget *widget, gpointer user_data)
{
  if (sql_destroy ())
    {
      g_print ("FATAL ERROR: SQL database could not be destroyed!\n");
      exit (EXIT_FAILURE);
    }
  else
    {
      g_print ("LOG: SQL database dropped\n");
    }
}
