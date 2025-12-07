#include "context.h"
#include <stdlib.h>

extern Context *
context_init (void)
{
  return calloc (1, sizeof (Context));
}

extern void
context_deinit (Context *ctx)
{
  free (ctx);
}
