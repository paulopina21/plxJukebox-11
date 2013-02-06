

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

/* Specification.  */
#include "vasnprintf.h"

#include <stdarg.h>

char *
asnprintf (char *resultbuf, size_t *lengthp, const char *format, ...)
{
  va_list args;
  char *result;

  va_start (args, format);
  result = vasnprintf (resultbuf, lengthp, format, args);
  va_end (args);
  return result;
}
