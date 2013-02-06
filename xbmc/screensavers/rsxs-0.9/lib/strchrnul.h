

#if HAVE_STRCHRNUL

/* Get strchrnul() declaration.  */
#include <string.h>

#else

/* Find the first occurrence of C in S or the final NUL byte.  */
extern char *strchrnul (const char *s, int c_in);

#endif
