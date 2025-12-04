#pragma once

#include <gtk/gtk.h>

typedef struct LogWidgets
{
  GtkWidget *container;
  GtkWidget *label;
  GtkWidget *text_view;
  GtkWidget *buffer;
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
extern GtkWidget *create_action_widgets (void);
extern GtkWidget *create_display_widgets (void);
