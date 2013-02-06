

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "libgettext.h"

/* @@ end of prolog @@ */


#undef gettext
#undef dgettext
#undef dcgettext
#undef textdomain
#undef bindtextdomain


char *
bindtextdomain (domainname, dirname)
     const char *domainname;
     const char *dirname;
{
  return bindtextdomain__ (domainname, dirname);
}


char *
dcgettext (domainname, msgid, category)
     const char *domainname;
     const char *msgid;
     int category;
{
  return dcgettext__ (domainname, msgid, category);
}


char *
dgettext (domainname, msgid)
     const char *domainname;
     const char *msgid;
{
  return dgettext__ (domainname, msgid);
}


char *
gettext (msgid)
     const char *msgid;
{
  return gettext__ (msgid);
}


char *
textdomain (domainname)
     const char *domainname;
{
  return textdomain__ (domainname);
}
