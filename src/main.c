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
  GtkWidget *window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "College Manager");
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 300);

  GtkWidget *paned = gtk_paned_new (GTK_ORIENTATION_HORIZONTAL);

  GtkWidget *left_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);
  gtk_widget_set_margin_top (left_box, 6);
  gtk_widget_set_margin_bottom (left_box, 6);
  gtk_widget_set_margin_start (left_box, 6);
  gtk_widget_set_margin_end (left_box, 6);

  GtkWidget *right_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);
  gtk_widget_set_margin_top (right_box, 6);
  gtk_widget_set_margin_bottom (right_box, 6);
  gtk_widget_set_margin_start (right_box, 6);
  gtk_widget_set_margin_end (right_box, 6);

  GtkWidget *create_button
      = gtk_button_new_with_label ("Initialize SQL database");
  g_signal_connect (create_button, "clicked",
                    G_CALLBACK (callback_init_database), NULL);

  GtkWidget *destroy_button = gtk_button_new_with_label ("Drop SQL database");
  g_signal_connect (destroy_button, "clicked",
                    G_CALLBACK (callback_drop_database), NULL);

  GtkWidget *placeholder_label = gtk_label_new ("placeholder");

  // set parent/child model:
  //
  // APP_WINDOW
  // L PANED
  //   L LEFT_BOX
  //   | L DB_CREATION_BUTTON
  //   | L DB_DESTRUCTION_BUTTON
  //   L RIGHT_BOX
  //     L PLACEHOLDER_LABEL
  gtk_window_set_child (GTK_WINDOW (window), paned);
  gtk_paned_set_start_child (GTK_PANED (paned), left_box);
  gtk_paned_set_end_child (GTK_PANED (paned), right_box);
  gtk_box_append (GTK_BOX (left_box), create_button);
  gtk_box_append (GTK_BOX (left_box), destroy_button);
  gtk_box_append (GTK_BOX (right_box), placeholder_label);

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
