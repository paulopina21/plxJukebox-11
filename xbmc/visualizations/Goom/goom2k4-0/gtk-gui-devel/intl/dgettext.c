

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#if defined HAVE_LOCALE_H || defined _LIBC
# include <locale.h>
#endif

#ifdef _LIBC
# include <libintl.h>
#else
# include "libgettext.h"
#endif

/* @@ end of prolog @@ */


#ifdef _LIBC
# define DGETTEXT __dgettext
# define DCGETTEXT __dcgettext
#else
# define DGETTEXT dgettext__
# define DCGETTEXT dcgettext__
#endif

/* Look up MSGID in the DOMAINNAME message catalog of the current
   LC_MESSAGES locale.  */
char *
DGETTEXT (domainname, msgid)
     const char *domainname;
     const char *msgid;
{
  return DCGETTEXT (domainname, msgid, LC_MESSAGES);
}

#ifdef _LIBC

weak_alias (__dgettext, dgettext);
#endif
