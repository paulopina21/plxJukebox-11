

#include <stddef.h>

/* Return a newly allocated copy of at most N bytes of STRING.
   In other words, return a copy of the initial segment of length N of
   STRING.  */
extern char *xstrndup (const char *string, size_t n);
