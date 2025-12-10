#include "widgets.h"
#include "callbacks.h"
#include "context.h"
#include "utils.h"
#include <gtk/gtk.h>

static gchar *
get_timestamp_string (void)
{
  gchar *time_string;
  GDateTime *now = g_date_time_new_now_local ();
  time_string = g_date_time_format (now, "[%F %T]");
  g_date_time_unref (now);
  return time_string;
}

static void
append_log (LogWidgets *log, char const *prefix, char const *msg,
            GtkTextTag *tag)
{
  gchar *time = get_timestamp_string ();
  GtkTextIter iterator;
  GtkTextBuffer *buffer
      = gtk_text_view_get_buffer (GTK_TEXT_VIEW (log->text_view));
  gtk_text_buffer_get_end_iter (buffer, &iterator);

  gtk_text_buffer_insert (buffer, &iterator, time, -1);
  gtk_text_buffer_insert (buffer, &iterator, " ", -1);
  gtk_text_buffer_insert_with_tags (buffer, &iterator, prefix, -1, tag, NULL);
  gtk_text_buffer_insert (buffer, &iterator, msg, -1);
  gtk_text_buffer_insert (buffer, &iterator, "\n", -1);

  scroll_to_bottom (GTK_SCROLLED_WINDOW (log->scroll_window));

  g_free (time);
}

extern GtkWidget *
create_log_widgets (Context *ctx)
{
  LogWidgets *log = g_new0 (LogWidgets, 1);
  ctx->log = log;

  log->container = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);
  gtk_widget_set_margin_top (log->container, 3);
  gtk_widget_set_margin_bottom (log->container, 3);
  gtk_widget_set_margin_start (log->container, 3);
  gtk_widget_set_margin_end (log->container, 3);

  log->label = gtk_label_new ("Log output:");

  log->scroll_window = gtk_scrolled_window_new ();

  log->text_view = gtk_text_view_new ();
  gtk_text_view_set_editable (GTK_TEXT_VIEW (log->text_view), FALSE);
  gtk_text_view_set_monospace (GTK_TEXT_VIEW (log->text_view), TRUE);
  gtk_widget_set_vexpand (log->text_view, TRUE);

  // also define the tag creations here
  GtkTextBuffer *buffer
      = gtk_text_view_get_buffer (GTK_TEXT_VIEW (log->text_view));
  log->tag_log = gtk_text_buffer_create_tag (
      buffer, "log", "foreground", "cyan", "weight", PANGO_WEIGHT_BOLD, NULL);
  log->tag_wrn
      = gtk_text_buffer_create_tag (buffer, "warn", "foreground", "yellow",
                                    "weight", PANGO_WEIGHT_BOLD, NULL);
  log->tag_err = gtk_text_buffer_create_tag (
      buffer, "error", "foreground", "red", "weight", PANGO_WEIGHT_BOLD, NULL);

  gtk_box_append (GTK_BOX (log->container), log->label);
  gtk_box_append (GTK_BOX (log->container), log->scroll_window);
  gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (log->scroll_window),
                                 log->text_view);

  // embed struct pointer to container
  g_object_set_data_full (G_OBJECT (log->container), "struct-data", log,
                          (GDestroyNotify)g_free);
  return log->container;
}

extern GtkWidget *
create_action_widgets (Context *ctx)
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
                    G_CALLBACK (callback_init_database), ctx);

  action->destroy_button = gtk_button_new_with_label ("Drop SQL database");
  g_signal_connect (action->destroy_button, "clicked",
                    G_CALLBACK (callback_drop_database), ctx);

  gtk_box_append (GTK_BOX (action->container), action->label);
  gtk_box_append (GTK_BOX (action->container), action->create_button);
  gtk_box_append (GTK_BOX (action->container), action->destroy_button);

  // embed struct pointer to container
  g_object_set_data_full (G_OBJECT (action->container), "struct-data", action,
                          (GDestroyNotify)g_free);
  return action->container;
}

extern GtkWidget *
create_display_widgets (Context *ctx)
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

extern LogWidgets *
get_data_log_widgets (GtkWidget *container)
{
  return g_object_get_data (G_OBJECT (container), "struct-data");
}

extern ActionWidgets *
get_data_action_widgets (GtkWidget *container)
{
  return g_object_get_data (G_OBJECT (container), "struct-data");
}

extern DisplayWidgets *
get_data_display_widgets (GtkWidget *container)
{
  return g_object_get_data (G_OBJECT (container), "struct-data");
}

extern void
append_log_notice (LogWidgets *log, char const *msg)
{
  append_log (log, "LOG: ", msg, log->tag_log);
}

extern void
append_log_warn (LogWidgets *log, char const *msg)
{
  append_log (log, "WARN: ", msg, log->tag_wrn);
}

extern void
append_log_error (LogWidgets *log, char const *msg)
{
  append_log (log, "ERROR: ", msg, log->tag_err);
}
