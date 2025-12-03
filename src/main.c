#include "sql.h"
#include <config.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

static void
callback_init_database ([[maybe_unused]] GtkWidget *widget,
                        [[maybe_unused]] gpointer user_data)
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

static void
callback_drop_database ([[maybe_unused]] GtkWidget *widget,
                        [[maybe_unused]] gpointer user_data)
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

static void
activate (GtkApplication *app, [[maybe_unused]] gpointer user_data)
{
  // app window
  GtkWidget *window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "College Manager");
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 300);

  // scrollable widget
  GtkWidget *scroll_window = gtk_scrolled_window_new ();

  // container which scrollable window uses
  GtkWidget *scroll_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);

  // create database button
  GtkWidget *create_button
      = gtk_button_new_with_label ("Initialize SQL database");
  g_signal_connect (create_button, "clicked",
                    G_CALLBACK (callback_init_database), NULL);

  // destroy database button
  GtkWidget *destroy_button = gtk_button_new_with_label ("Drop SQL database");
  g_signal_connect (destroy_button, "clicked",
                    G_CALLBACK (callback_drop_database), NULL);

  // set parent/child model:
  //
  // APP_WINDOW
  // L SCROLL_WINDOW
  //   L SCROLL_BOX
  //     L DB_CREATION_BUTTON
  //     L DB_DESTRUCTION_BUTTON
  gtk_window_set_child (GTK_WINDOW (window), scroll_window);
  gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scroll_window),
                                 scroll_box);
  gtk_box_append (GTK_BOX (scroll_box), create_button);
  gtk_box_append (GTK_BOX (scroll_box), destroy_button);

  // render app window and all children
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
