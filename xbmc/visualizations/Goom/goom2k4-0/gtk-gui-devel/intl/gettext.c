

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#ifdef _LIBC
# define __need_NULL
# include <stddef.h>
#else
# ifdef STDC_HEADERS
#  include <stdlib.h>		/* Just for NULL.  */
# else
#  ifdef HAVE_STRING_H
#   include <string.h>
#  else
#   define NULL ((void *) 0)
#  endif
# endif
#endif

#ifdef _LIBC
# include <libintl.h>
#else
# include "libgettext.h"
#endif

/* @@ end of prolog @@ */


#ifdef _LIBC
# define GETTEXT __gettext
# define DGETTEXT __dgettext
#else
# define GETTEXT gettext__
# define DGETTEXT dgettext__
#endif

/* Look up MSGID in the current default message catalog for the current
   LC_MESSAGES locale.  If not found, returns MSGID itself (the default
   text).  */
char *
GETTEXT (msgid)
     const char *msgid;
{
  return DGETTEXT (NULL, msgid);
}

#ifdef _LIBC

weak_alias (__gettext, gettext);
#endif
