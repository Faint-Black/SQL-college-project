#include "widgets.h"
#include "callbacks.h"
#include <gtk/gtk.h>

extern GtkWidget *
create_log_widgets (void)
{
  LogWidgets *log = g_new0 (LogWidgets, 1);

  log->container = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);

  log->label = gtk_label_new ("Log output:");

  log->text_view = gtk_text_view_new ();
  gtk_text_view_set_editable (GTK_TEXT_VIEW (log->text_view), FALSE);
  gtk_text_view_set_monospace (GTK_TEXT_VIEW (log->text_view), TRUE);

  gtk_box_append (GTK_BOX (log->container), log->label);
  gtk_box_append (GTK_BOX (log->container), log->text_view);

  // embed struct pointer to container
  g_object_set_data_full (G_OBJECT (log->container), "struct-data", log,
                          (GDestroyNotify)g_free);
  return log->container;
}

extern GtkWidget *
create_action_widgets (void)
{
  ActionWidgets *action = g_new0 (ActionWidgets, 1);

  action->container = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);
  gtk_widget_set_margin_top (action->container, 6);
  gtk_widget_set_margin_bottom (action->container, 6);
  gtk_widget_set_margin_start (action->container, 6);
  gtk_widget_set_margin_end (action->container, 6);

  action->label = gtk_label_new ("Actions:");

  action->create_button
      = gtk_button_new_with_label ("Initialize SQL database");
  g_signal_connect (action->create_button, "clicked",
                    G_CALLBACK (callback_init_database), NULL);

  action->destroy_button = gtk_button_new_with_label ("Drop SQL database");
  g_signal_connect (action->destroy_button, "clicked",
                    G_CALLBACK (callback_drop_database), NULL);

  gtk_box_append (GTK_BOX (action->container), action->label);
  gtk_box_append (GTK_BOX (action->container), action->create_button);
  gtk_box_append (GTK_BOX (action->container), action->destroy_button);

  // embed struct pointer to container
  g_object_set_data_full (G_OBJECT (action->container), "struct-data", action,
                          (GDestroyNotify)g_free);
  return action->container;
}

extern GtkWidget *
create_display_widgets (void)
{
  DisplayWidgets *display = g_new0 (DisplayWidgets, 1);

  display->container = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);
  gtk_widget_set_margin_top (display->container, 6);
  gtk_widget_set_margin_bottom (display->container, 6);
  gtk_widget_set_margin_start (display->container, 6);
  gtk_widget_set_margin_end (display->container, 6);

  display->label = gtk_label_new ("placeholder");

  gtk_box_append (GTK_BOX (display->container), display->label);

  // embed struct pointer to container
  g_object_set_data_full (G_OBJECT (display->container), "struct-data",
                          display, (GDestroyNotify)g_free);
  return display->container;
}
