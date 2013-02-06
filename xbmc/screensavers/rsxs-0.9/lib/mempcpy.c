

/* Specification.  */
#include "mempcpy.h"

#include <string.h>

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
void *
mempcpy (void *dest, const void *src, size_t n)
{
  return (char *) memcpy (dest, src, n) + n;
}
