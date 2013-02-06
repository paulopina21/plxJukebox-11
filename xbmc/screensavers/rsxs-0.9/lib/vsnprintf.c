

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

/* Specification.  */
#include "vsnprintf.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vasnprintf.h"

/* Print formatted output to string STR.  Similar to vsprintf, but
   additional length SIZE limit how much is written into STR.  Returns
   string length of formatted string (which may be larger than SIZE).
   STR may be NULL, in which case nothing will be written.  On error,
   return a negative value. */
int
vsnprintf (char *str, size_t size, const char *format, va_list args)
{
  char *output;
  size_t len;

  len = size;
  output = vasnprintf (str, &len, format, args);

  if (!output)
    return -1;

  if (str != NULL)
    if (len > size - 1) /* equivalent to: (size > 0 && len >= size) */
      str[size - 1] = '\0';

  if (output != str)
    free (output);

  return len;
}
