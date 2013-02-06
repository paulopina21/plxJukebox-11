

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

/* Specification.  */
#include "strnlen1.h"

#include <string.h>

/* Find the length of STRING + 1, but scan at most MAXLEN bytes.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
/* This is the same as strnlen (string, maxlen - 1) + 1.  */
size_t
strnlen1 (const char *string, size_t maxlen)
{
  const char *end = memchr (string, '\0', maxlen);
  if (end != NULL)
    return end - string + 1;
  else
    return maxlen;
}
