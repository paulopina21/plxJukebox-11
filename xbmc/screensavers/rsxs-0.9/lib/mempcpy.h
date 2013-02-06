

#ifndef mempcpy

# if HAVE_MEMPCPY

/* Get mempcpy() declaration.  */
#  include <string.h>

# else

/* Get size_t */
#  include <stddef.h>

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
extern void *mempcpy (void *dest, const void *src, size_t n);

# endif

#endif
