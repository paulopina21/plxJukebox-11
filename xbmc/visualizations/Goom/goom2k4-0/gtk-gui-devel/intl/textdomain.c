

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#if defined STDC_HEADERS || defined _LIBC
# include <stdlib.h>
#endif

#if defined STDC_HEADERS || defined HAVE_STRING_H || defined _LIBC
# include <string.h>
#else
# include <strings.h>
# ifndef memcpy
#  define memcpy(Dst, Src, Num) bcopy (Src, Dst, Num)
# endif
#endif

#ifdef _LIBC
# include <libintl.h>
#else
# include "libgettext.h"
#endif

/* @@ end of prolog @@ */

/* Name of the default text domain.  */
extern const char _nl_default_default_domain[];

/* Default text domain in which entries for gettext(3) are to be found.  */
extern const char *_nl_current_default_domain;



#ifdef _LIBC
# define TEXTDOMAIN __textdomain
# ifndef strdup
#  define strdup(str) __strdup (str)
# endif
#else
# define TEXTDOMAIN textdomain__
#endif

/* Set the current default message catalog to DOMAINNAME.
   If DOMAINNAME is null, return the current default.
   If DOMAINNAME is "", reset to the default of "messages".  */
char *
TEXTDOMAIN (domainname)
     const char *domainname;
{
  char *old;

  /* A NULL pointer requests the current setting.  */
  if (domainname == NULL)
    return (char *) _nl_current_default_domain;

  old = (char *) _nl_current_default_domain;

  /* If domain name is the null string set to default domain "messages".  */
  if (domainname[0] == '\0'
      || strcmp (domainname, _nl_default_default_domain) == 0)
    _nl_current_default_domain = _nl_default_default_domain;
  else
    {
      /* If the following malloc fails `_nl_current_default_domain'
	 will be NULL.  This value will be returned and so signals we
	 are out of core.  */
#if defined _LIBC || defined HAVE_STRDUP
      _nl_current_default_domain = strdup (domainname);
#else
      size_t len = strlen (domainname) + 1;
      char *cp = (char *) malloc (len);
      if (cp != NULL)
	memcpy (cp, domainname, len);
      _nl_current_default_domain = cp;
#endif
    }

  if (old != _nl_default_default_domain)
    free (old);

  return (char *) _nl_current_default_domain;
}

#ifdef _LIBC

weak_alias (__textdomain, textdomain);
#endif
