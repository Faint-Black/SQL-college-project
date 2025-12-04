#pragma once

#include <gtk/gtk.h>

typedef struct LogWidgets
{
  GtkWidget *container;
  GtkWidget *label;
  GtkWidget *scroll_window;
  GtkWidget *text_view;
  GtkTextTag *tag_log;
  GtkTextTag *tag_wrn;
  GtkTextTag *tag_err;
} LogWidgets;

typedef struct ActionWidgets
{
  GtkWidget *container;
  GtkWidget *label;
  GtkWidget *create_button;
  GtkWidget *destroy_button;
} ActionWidgets;

typedef struct DisplayWidgets
{
  GtkWidget *container;
  GtkWidget *label;
} DisplayWidgets;

extern GtkWidget *create_log_widgets (void);
extern GtkWidget *create_action_widgets (LogWidgets *log);
extern GtkWidget *create_display_widgets (LogWidgets *log);

extern LogWidgets *get_data_log_widgets (GtkWidget *container);
extern ActionWidgets *get_data_action_widgets (GtkWidget *container);
extern DisplayWidgets *get_data_display_widgets (GtkWidget *container);

extern void append_log_notice (LogWidgets *log, char const *msg);
extern void append_log_warn (LogWidgets *log, char const *msg);
extern void append_log_error (LogWidgets *log, char const *msg);
