

#ifndef GNULIB_SIZE_MAX_H
#define GNULIB_SIZE_MAX_H

/* Get SIZE_MAX declaration on systems like Solaris 7/8/9.  */
# include <limits.h>
/* Get SIZE_MAX declaration on systems like glibc 2.  */
# if HAVE_STDINT_H
#  include <stdint.h>
# endif
/* On systems where these include files don't define it, SIZE_MAX is defined
   in config.h.  */

#endif 
