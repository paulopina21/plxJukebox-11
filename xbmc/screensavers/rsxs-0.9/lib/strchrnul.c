

/* Specification.  */
#include "strchrnul.h"

/* Find the first occurrence of C in S or the final NUL byte.  */
char *
strchrnul (const char *s, int c_in)
{
  char c = c_in;
  while (*s && (*s != c))
    s++;

  return (char *) s;
}
