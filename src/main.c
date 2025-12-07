#include "context.h"
#include "sql.h"
#include "widgets.h"
#include <config.h>
#include <gtk/gtk.h>

static void
activate (GtkApplication *app, gpointer ctx)
{
  GtkWidget *window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "College Manager");
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 300);

  GtkWidget *h_paned = gtk_paned_new (GTK_ORIENTATION_HORIZONTAL);
  GtkWidget *v_paned = gtk_paned_new (GTK_ORIENTATION_VERTICAL);
  GtkWidget *log_panel = create_log_widgets (ctx);
  GtkWidget *display_panel = create_display_widgets (ctx);
  GtkWidget *actions_panel = create_action_widgets (ctx);

  // APP_WINDOW
  // L HORIZONTAL_PANED
  //   L (left)VERTICAL_PANED
  //   | L (top)ACTIONS_PANEL
  //   | L (bottom)LOG_PANEL
  //   L (right)DISPLAY_PANEL
  gtk_window_set_child (GTK_WINDOW (window), h_paned);
  gtk_paned_set_start_child (GTK_PANED (h_paned), v_paned);
  gtk_paned_set_end_child (GTK_PANED (h_paned), display_panel);
  gtk_paned_set_start_child (GTK_PANED (v_paned), actions_panel);
  gtk_paned_set_end_child (GTK_PANED (v_paned), log_panel);

  gtk_window_present (GTK_WINDOW (window));
}

int
main (int argc, char **argv)
{
  Context *context = context_init ();

  MYSQL *conn = sql_connect (context, DB_USR, DB_PWD);
  if (conn == NULL)
    {
      printf ("FATAL ERROR: sql_connect() failed\n");
      context_deinit (context);
      return EXIT_FAILURE;
    }

  GtkApplication *app;
  int status;
  app = gtk_application_new ("org.gtk.collegemanager",
                             G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), context);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  sql_disconnect (conn);
  context_deinit (context);
  return status;
}
