#pragma once

#include "context.h"
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

typedef struct RoleForm
{
  GtkWidget *container;
  GtkWidget *name_entry;
} RoleForm;

typedef struct UserAccountForm
{
  GtkWidget *container;
  GtkWidget *name_entry;
  GtkWidget *email_entry;
  GtkWidget *password_entry;
  GtkWidget *phone_entry;
} UserAccountForm;

typedef struct PeriodForm
{
  GtkWidget *container;
  GtkWidget *name_entry;
  GtkWidget *start_date;
  GtkWidget *end_date;
} PeriodForm;

typedef struct CourseForm
{
  GtkWidget *container;
  GtkWidget *code_entry;
  GtkWidget *title_entry;
  GtkWidget *description_entry;
  GtkWidget *max_students_entry;
} CourseForm;

typedef struct ClassForm
{
  GtkWidget *container;
  GtkWidget *course_id_entry;
  GtkWidget *period_id_entry;
  GtkWidget *professor_id_entry;
  GtkWidget *start_date;
  GtkWidget *end_date;
  GtkWidget *max_students_entry;
  GtkWidget *status_dropdown;
} ClassForm;

typedef struct EnrollmentForm
{
  GtkWidget *container;
  GtkWidget *class_id_entry;
  GtkWidget *student_id_entry;
  GtkWidget *status_dropdown;
  GtkWidget *priority_check;
} EnrollmentForm;

typedef struct MaterialForm
{
  GtkWidget *container;
  GtkWidget *class_id_entry;
  GtkWidget *title_entry;
  GtkWidget *description_entry;
  GtkWidget *file_url_entry;
  GtkWidget *uploaded_by_entry;
} MaterialForm;

typedef struct ActivityForm
{
  GtkWidget *container;
  GtkWidget *class_id_entry;
  GtkWidget *title_entry;
  GtkWidget *description_entry;
  GtkWidget *due_date_entry;
  GtkWidget *weight_entry;
  GtkWidget *max_score_entry;
  GtkWidget *created_by_entry;
} ActivityForm;

typedef struct SubmissionForm
{
  GtkWidget *container;
  GtkWidget *activity_id_entry;
  GtkWidget *student_id_entry;
  GtkWidget *submitted_at_entry;
  GtkWidget *content_url_entry;
  GtkWidget *grade_entry;
  GtkWidget *feedback_entry;
} SubmissionForm;

typedef struct FormsWidgets
{
  GtkWidget *container;
  GtkWidget *default_form;
  GtkWidget *role_form;
  GtkWidget *user_account_form;
  GtkWidget *period_form;
  GtkWidget *course_form;
  GtkWidget *class_form;
  GtkWidget *enrollment_form;
  GtkWidget *material_form;
  GtkWidget *activity_form;
  GtkWidget *submission_form;
} FormsWidgets;

extern GtkWidget *create_log_widgets (Context *ctx);
extern GtkWidget *create_action_widgets (Context *ctx);
extern GtkWidget *create_display_widgets (Context *ctx);
extern GtkWidget *create_role_form (Context *ctx);
extern GtkWidget *create_user_account_form (Context *ctx);
extern GtkWidget *create_period_form (Context *ctx);
extern GtkWidget *create_course_form (Context *ctx);
extern GtkWidget *create_class_form (Context *ctx);
extern GtkWidget *create_enrollment_form (Context *ctx);
extern GtkWidget *create_material_form (Context *ctx);
extern GtkWidget *create_activity_form (Context *ctx);
extern GtkWidget *create_submission_form (Context *ctx);
extern GtkWidget *create_forms_widgets (Context *ctx);

extern LogWidgets *get_data_log_widgets (GtkWidget *container);
extern ActionWidgets *get_data_action_widgets (GtkWidget *container);
extern DisplayWidgets *get_data_display_widgets (GtkWidget *container);
extern RoleForm *get_data_role_form (GtkWidget *container);
extern UserAccountForm *get_data_user_account_form (GtkWidget *container);
extern PeriodForm *get_data_period_form (GtkWidget *container);
extern CourseForm *get_data_course_form (GtkWidget *container);
extern ClassForm *get_data_class_form (GtkWidget *container);
extern EnrollmentForm *get_data_enrollment_form (GtkWidget *container);
extern MaterialForm *get_data_material_form (GtkWidget *container);
extern ActivityForm *get_data_activity_form (GtkWidget *container);
extern SubmissionForm *get_data_submission_form (GtkWidget *container);
extern FormsWidgets *get_data_forms_widgets (GtkWidget *container);

extern void append_log_notice (LogWidgets *log, char const *msg);
extern void append_log_warn (LogWidgets *log, char const *msg);
extern void append_log_error (LogWidgets *log, char const *msg);
