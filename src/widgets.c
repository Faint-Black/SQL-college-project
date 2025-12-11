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

  display->label = gtk_label_new ("Nothing selected yet");

  gtk_box_append (GTK_BOX (display->container), display->label);

  g_object_set_data_full (G_OBJECT (display->container), "struct-data",
                          display, (GDestroyNotify)g_free);
  return display->container;
}

extern GtkWidget *
create_role_form (Context *ctx)
{
  RoleForm *form = g_new0 (RoleForm, 1);

  form->container = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);

  GtkWidget *name_label = gtk_label_new ("Role name:");
  form->name_entry = gtk_entry_new ();

  gtk_box_append (GTK_BOX (form->container), name_label);
  gtk_box_append (GTK_BOX (form->container), form->name_entry);

  g_object_set_data_full (G_OBJECT (form->container), "struct-data", form,
                          (GDestroyNotify)g_free);
  return form->container;
}

extern GtkWidget *
create_user_account_form (Context *ctx)
{
  UserAccountForm *form = g_new0 (UserAccountForm, 1);
  form->container = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);

  GtkWidget *name_label = gtk_label_new ("Name:");
  GtkWidget *email_label = gtk_label_new ("Email:");
  GtkWidget *password_label = gtk_label_new ("Password:");
  GtkWidget *phone_label = gtk_label_new ("Phone:");

  form->name_entry = gtk_entry_new ();
  form->email_entry = gtk_entry_new ();
  form->password_entry = gtk_entry_new ();
  gtk_entry_set_visibility (GTK_ENTRY (form->password_entry), FALSE);
  gtk_entry_set_input_purpose (GTK_ENTRY (form->password_entry),
                               GTK_INPUT_PURPOSE_PASSWORD);
  form->phone_entry = gtk_entry_new ();

  gtk_box_append (GTK_BOX (form->container), name_label);
  gtk_box_append (GTK_BOX (form->container), form->name_entry);

  gtk_box_append (GTK_BOX (form->container), email_label);
  gtk_box_append (GTK_BOX (form->container), form->email_entry);

  gtk_box_append (GTK_BOX (form->container), password_label);
  gtk_box_append (GTK_BOX (form->container), form->password_entry);

  gtk_box_append (GTK_BOX (form->container), phone_label);
  gtk_box_append (GTK_BOX (form->container), form->phone_entry);

  g_object_set_data_full (G_OBJECT (form->container), "struct-data", form,
                          (GDestroyNotify)g_free);
  return form->container;
}

extern GtkWidget *
create_period_form (Context *ctx)
{
  PeriodForm *form = g_new0 (PeriodForm, 1);
  form->container = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);

  GtkWidget *name_label = gtk_label_new ("Period name:");
  GtkWidget *start_label = gtk_label_new ("Start date (YYYY-MM-DD):");
  GtkWidget *end_label = gtk_label_new ("End date (YYYY-MM-DD):");

  form->name_entry = gtk_entry_new ();
  form->start_date = gtk_entry_new ();
  form->end_date = gtk_entry_new ();

  gtk_box_append (GTK_BOX (form->container), name_label);
  gtk_box_append (GTK_BOX (form->container), form->name_entry);

  gtk_box_append (GTK_BOX (form->container), start_label);
  gtk_box_append (GTK_BOX (form->container), form->start_date);

  gtk_box_append (GTK_BOX (form->container), end_label);
  gtk_box_append (GTK_BOX (form->container), form->end_date);

  g_object_set_data_full (G_OBJECT (form->container), "struct-data", form,
                          (GDestroyNotify)g_free);
  return form->container;
}

extern GtkWidget *
create_course_form (Context *ctx)
{
  CourseForm *form = g_new0 (CourseForm, 1);
  form->container = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);

  GtkWidget *code_label = gtk_label_new ("Course code:");
  GtkWidget *title_label = gtk_label_new ("Course title:");
  GtkWidget *desc_label = gtk_label_new ("Description:");
  GtkWidget *max_label = gtk_label_new ("Max students:");

  form->code_entry = gtk_entry_new ();
  form->title_entry = gtk_entry_new ();
  form->description_entry = gtk_text_view_new ();
  form->max_students_entry = gtk_entry_new ();

  gtk_box_append (GTK_BOX (form->container), code_label);
  gtk_box_append (GTK_BOX (form->container), form->code_entry);

  gtk_box_append (GTK_BOX (form->container), title_label);
  gtk_box_append (GTK_BOX (form->container), form->title_entry);

  gtk_box_append (GTK_BOX (form->container), desc_label);
  gtk_box_append (GTK_BOX (form->container), form->description_entry);

  gtk_box_append (GTK_BOX (form->container), max_label);
  gtk_box_append (GTK_BOX (form->container), form->max_students_entry);

  g_object_set_data_full (G_OBJECT (form->container), "struct-data", form,
                          (GDestroyNotify)g_free);
  return form->container;
}

extern GtkWidget *
create_class_form (Context *ctx)
{
  ClassForm *form = g_new0 (ClassForm, 1);
  form->container = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);

  GtkWidget *course_label = gtk_label_new ("Course ID:");
  GtkWidget *period_label = gtk_label_new ("Period ID:");
  GtkWidget *prof_label = gtk_label_new ("Professor ID:");
  GtkWidget *start_label = gtk_label_new ("Start date:");
  GtkWidget *end_label = gtk_label_new ("End date:");
  GtkWidget *max_label = gtk_label_new ("Max students:");
  GtkWidget *status_label = gtk_label_new ("Status:");

  form->course_id_entry = gtk_entry_new ();
  form->period_id_entry = gtk_entry_new ();
  form->professor_id_entry = gtk_entry_new ();
  form->start_date = gtk_entry_new ();
  form->end_date = gtk_entry_new ();
  form->max_students_entry = gtk_entry_new ();

  static char const *const options[] = {
    "OPEN",
    "CLOSED",
    "ARCHIVED",
    NULL,
  };
  form->status_dropdown = gtk_drop_down_new_from_strings (options);

  gtk_box_append (GTK_BOX (form->container), course_label);
  gtk_box_append (GTK_BOX (form->container), form->course_id_entry);

  gtk_box_append (GTK_BOX (form->container), period_label);
  gtk_box_append (GTK_BOX (form->container), form->period_id_entry);

  gtk_box_append (GTK_BOX (form->container), prof_label);
  gtk_box_append (GTK_BOX (form->container), form->professor_id_entry);

  gtk_box_append (GTK_BOX (form->container), start_label);
  gtk_box_append (GTK_BOX (form->container), form->start_date);

  gtk_box_append (GTK_BOX (form->container), end_label);
  gtk_box_append (GTK_BOX (form->container), form->end_date);

  gtk_box_append (GTK_BOX (form->container), max_label);
  gtk_box_append (GTK_BOX (form->container), form->max_students_entry);

  gtk_box_append (GTK_BOX (form->container), status_label);
  gtk_box_append (GTK_BOX (form->container), form->status_dropdown);

  g_object_set_data_full (G_OBJECT (form->container), "struct-data", form,
                          (GDestroyNotify)g_free);
  return form->container;
}

extern GtkWidget *
create_enrollment_form (Context *ctx)
{
  EnrollmentForm *form = g_new0 (EnrollmentForm, 1);
  form->container = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);

  GtkWidget *class_label = gtk_label_new ("Class ID:");
  GtkWidget *student_label = gtk_label_new ("Student ID:");
  GtkWidget *status_label = gtk_label_new ("Status:");
  GtkWidget *priority_label = gtk_label_new ("Priority:");

  form->class_id_entry = gtk_entry_new ();
  form->student_id_entry = gtk_entry_new ();

  static char const *const options[] = {
    "WAITLIST", "ENROLLED", "REJECTED", "CANCELLED", NULL,
  };
  form->status_dropdown = gtk_drop_down_new_from_strings (options);

  form->priority_check = gtk_check_button_new ();

  gtk_box_append (GTK_BOX (form->container), class_label);
  gtk_box_append (GTK_BOX (form->container), form->class_id_entry);

  gtk_box_append (GTK_BOX (form->container), student_label);
  gtk_box_append (GTK_BOX (form->container), form->student_id_entry);

  gtk_box_append (GTK_BOX (form->container), status_label);
  gtk_box_append (GTK_BOX (form->container), form->status_dropdown);

  gtk_box_append (GTK_BOX (form->container), priority_label);
  gtk_box_append (GTK_BOX (form->container), form->priority_check);

  g_object_set_data_full (G_OBJECT (form->container), "struct-data", form,
                          (GDestroyNotify)g_free);
  return form->container;
}

extern GtkWidget *
create_material_form (Context *ctx)
{
  MaterialForm *form = g_new0 (MaterialForm, 1);
  form->container = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);

  GtkWidget *class_label = gtk_label_new ("Class ID:");
  GtkWidget *title_label = gtk_label_new ("Title:");
  GtkWidget *desc_label = gtk_label_new ("Description:");
  GtkWidget *file_label = gtk_label_new ("File URL:");
  GtkWidget *up_label = gtk_label_new ("Uploaded by (user ID):");

  form->class_id_entry = gtk_entry_new ();
  form->title_entry = gtk_entry_new ();
  form->description_entry = gtk_text_view_new ();
  form->file_url_entry = gtk_entry_new ();
  form->uploaded_by_entry = gtk_entry_new ();

  gtk_box_append (GTK_BOX (form->container), class_label);
  gtk_box_append (GTK_BOX (form->container), form->class_id_entry);

  gtk_box_append (GTK_BOX (form->container), title_label);
  gtk_box_append (GTK_BOX (form->container), form->title_entry);

  gtk_box_append (GTK_BOX (form->container), desc_label);
  gtk_box_append (GTK_BOX (form->container), form->description_entry);

  gtk_box_append (GTK_BOX (form->container), file_label);
  gtk_box_append (GTK_BOX (form->container), form->file_url_entry);

  gtk_box_append (GTK_BOX (form->container), up_label);
  gtk_box_append (GTK_BOX (form->container), form->uploaded_by_entry);

  g_object_set_data_full (G_OBJECT (form->container), "struct-data", form,
                          (GDestroyNotify)g_free);
  return form->container;
}

extern GtkWidget *
create_activity_form (Context *ctx)
{
  ActivityForm *form = g_new0 (ActivityForm, 1);
  form->container = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);

  GtkWidget *class_label = gtk_label_new ("Class ID:");
  GtkWidget *title_label = gtk_label_new ("Title:");
  GtkWidget *desc_label = gtk_label_new ("Description:");
  GtkWidget *due_label = gtk_label_new ("Due date (YYYY-MM-DD HH:MM):");
  GtkWidget *weight_label = gtk_label_new ("Weight:");
  GtkWidget *max_label = gtk_label_new ("Max score:");
  GtkWidget *created_label = gtk_label_new ("Created by (user ID):");

  form->class_id_entry = gtk_entry_new ();
  form->title_entry = gtk_entry_new ();
  form->description_entry = gtk_text_view_new ();
  form->due_date_entry = gtk_entry_new ();
  form->weight_entry = gtk_entry_new ();
  form->max_score_entry = gtk_entry_new ();
  form->created_by_entry = gtk_entry_new ();

  gtk_box_append (GTK_BOX (form->container), class_label);
  gtk_box_append (GTK_BOX (form->container), form->class_id_entry);

  gtk_box_append (GTK_BOX (form->container), title_label);
  gtk_box_append (GTK_BOX (form->container), form->title_entry);

  gtk_box_append (GTK_BOX (form->container), desc_label);
  gtk_box_append (GTK_BOX (form->container), form->description_entry);

  gtk_box_append (GTK_BOX (form->container), due_label);
  gtk_box_append (GTK_BOX (form->container), form->due_date_entry);

  gtk_box_append (GTK_BOX (form->container), weight_label);
  gtk_box_append (GTK_BOX (form->container), form->weight_entry);

  gtk_box_append (GTK_BOX (form->container), max_label);
  gtk_box_append (GTK_BOX (form->container), form->max_score_entry);

  gtk_box_append (GTK_BOX (form->container), created_label);
  gtk_box_append (GTK_BOX (form->container), form->created_by_entry);

  g_object_set_data_full (G_OBJECT (form->container), "struct-data", form,
                          (GDestroyNotify)g_free);
  return form->container;
}

extern GtkWidget *
create_submission_form (Context *ctx)
{
  SubmissionForm *form = g_new0 (SubmissionForm, 1);
  form->container = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);

  GtkWidget *act_label = gtk_label_new ("Activity ID:");
  GtkWidget *stu_label = gtk_label_new ("Student ID:");
  GtkWidget *sub_label = gtk_label_new ("Submitted at (YYYY-MM-DD HH:MM):");
  GtkWidget *url_label = gtk_label_new ("Content URL:");
  GtkWidget *grade_label = gtk_label_new ("Grade:");
  GtkWidget *fb_label = gtk_label_new ("Feedback:");

  form->activity_id_entry = gtk_entry_new ();
  form->student_id_entry = gtk_entry_new ();
  form->submitted_at_entry = gtk_entry_new ();
  form->content_url_entry = gtk_entry_new ();
  form->grade_entry = gtk_entry_new ();
  form->feedback_entry = gtk_text_view_new ();

  gtk_box_append (GTK_BOX (form->container), act_label);
  gtk_box_append (GTK_BOX (form->container), form->activity_id_entry);

  gtk_box_append (GTK_BOX (form->container), stu_label);
  gtk_box_append (GTK_BOX (form->container), form->student_id_entry);

  gtk_box_append (GTK_BOX (form->container), sub_label);
  gtk_box_append (GTK_BOX (form->container), form->submitted_at_entry);

  gtk_box_append (GTK_BOX (form->container), url_label);
  gtk_box_append (GTK_BOX (form->container), form->content_url_entry);

  gtk_box_append (GTK_BOX (form->container), grade_label);
  gtk_box_append (GTK_BOX (form->container), form->grade_entry);

  gtk_box_append (GTK_BOX (form->container), fb_label);
  gtk_box_append (GTK_BOX (form->container), form->feedback_entry);

  g_object_set_data_full (G_OBJECT (form->container), "struct-data", form,
                          (GDestroyNotify)g_free);
  return form->container;
}

extern GtkWidget *
create_forms_widgets (Context *ctx)
{
  FormsWidgets *forms = g_new0 (FormsWidgets, 1);
  forms->container = gtk_stack_new ();

  forms->default_form = create_display_widgets (ctx);
  forms->role_form = create_role_form (ctx);
  forms->user_account_form = create_user_account_form (ctx);
  forms->period_form = create_period_form (ctx);
  forms->course_form = create_course_form (ctx);
  forms->class_form = create_class_form (ctx);
  forms->enrollment_form = create_enrollment_form (ctx);
  forms->material_form = create_material_form (ctx);
  forms->activity_form = create_activity_form (ctx);
  forms->submission_form = create_submission_form (ctx);

  gtk_stack_add_named (GTK_STACK (forms->container), forms->default_form,
                       "default");
  gtk_stack_add_named (GTK_STACK (forms->container), forms->role_form,
                       "role_form");
  gtk_stack_add_named (GTK_STACK (forms->container), forms->user_account_form,
                       "user_account_form");
  gtk_stack_add_named (GTK_STACK (forms->container), forms->period_form,
                       "period_form");
  gtk_stack_add_named (GTK_STACK (forms->container), forms->course_form,
                       "course_form");
  gtk_stack_add_named (GTK_STACK (forms->container), forms->class_form,
                       "class_form");
  gtk_stack_add_named (GTK_STACK (forms->container), forms->enrollment_form,
                       "enrollment_form");
  gtk_stack_add_named (GTK_STACK (forms->container), forms->material_form,
                       "material_form");
  gtk_stack_add_named (GTK_STACK (forms->container), forms->activity_form,
                       "activity_form");
  gtk_stack_add_named (GTK_STACK (forms->container), forms->submission_form,
                       "submission_form");

  gtk_stack_set_visible_child_name (GTK_STACK (forms->container), "default");

  g_object_set_data_full (G_OBJECT (forms->container), "struct-data", forms,
                          (GDestroyNotify)g_free);
  return forms->container;
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

extern RoleForm *
get_data_role_form (GtkWidget *container)
{
  return g_object_get_data (G_OBJECT (container), "struct-data");
}

extern UserAccountForm *
get_data_user_account_form (GtkWidget *container)
{
  return g_object_get_data (G_OBJECT (container), "struct-data");
}

extern PeriodForm *
get_data_period_form (GtkWidget *container)
{
  return g_object_get_data (G_OBJECT (container), "struct-data");
}

extern CourseForm *
get_data_course_form (GtkWidget *container)
{
  return g_object_get_data (G_OBJECT (container), "struct-data");
}

extern ClassForm *
get_data_class_form (GtkWidget *container)
{
  return g_object_get_data (G_OBJECT (container), "struct-data");
}

extern EnrollmentForm *
get_data_enrollment_form (GtkWidget *container)
{
  return g_object_get_data (G_OBJECT (container), "struct-data");
}

extern MaterialForm *
get_data_material_form (GtkWidget *container)
{
  return g_object_get_data (G_OBJECT (container), "struct-data");
}

extern ActivityForm *
get_data_activity_form (GtkWidget *container)
{
  return g_object_get_data (G_OBJECT (container), "struct-data");
}

extern SubmissionForm *
get_data_submission_form (GtkWidget *container)
{
  return g_object_get_data (G_OBJECT (container), "struct-data");
}

extern FormsWidgets *
get_data_forms_widgets (GtkWidget *container)
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
