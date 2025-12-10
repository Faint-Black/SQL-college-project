#include "utils.h"

extern void
scroll_to_bottom (GtkScrolledWindow *sw)
{
  GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment (sw);
  double upper = gtk_adjustment_get_upper (adj);
  double page = gtk_adjustment_get_page_size (adj);

  gtk_adjustment_set_value (adj, upper - page);
}
