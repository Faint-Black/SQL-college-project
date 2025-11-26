#include "sql.h"
#include <config.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

static void
hello_world_print (GtkWidget *widget, gpointer user_data)
{
  g_print ("Hello World!\n");
}

static void
activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "College Manager");
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 300);

  button = gtk_button_new_with_label ("Hello SQL Manager");
  g_signal_connect (button, "clicked", G_CALLBACK (hello_world_print), NULL);
  gtk_window_set_child (GTK_WINDOW (window), button);

  gtk_window_present (GTK_WINDOW (window));
}

int
main (int argc, char **argv)
{
  // init SQL
  if (sql_init ())
    {
      printf ("FATAL ERROR: SQL could not initialize!\n");
      return EXIT_FAILURE;
    }
  else
    {
      printf ("LOG: SQL database fully initialized\n");
    }

  // init GTK4
  GtkApplication *app;
  int status;
  app = gtk_application_new ("org.gtk.collegemanager",
                             G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
