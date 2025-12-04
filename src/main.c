#include "widgets.h"
#include <config.h>
#include <gtk/gtk.h>

static void
activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "College Manager");
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 300);

  GtkWidget *h_paned = gtk_paned_new (GTK_ORIENTATION_HORIZONTAL);
  GtkWidget *v_paned = gtk_paned_new (GTK_ORIENTATION_VERTICAL);
  GtkWidget *display_panel = create_display_widgets ();
  GtkWidget *actions_panel = create_action_widgets ();
  GtkWidget *log_panel = create_log_widgets ();

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

  // set master widget
  gtk_window_present (GTK_WINDOW (window));
}

int
main (int argc, char **argv)
{
  GtkApplication *app;
  int status;
  app = gtk_application_new ("org.gtk.collegemanager",
                             G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
