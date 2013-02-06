

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "dirname.h"

/* Remove trailing slashes from FILE.  Return true if a trailing slash
   was removed.  This is useful when using file name completion from a
   shell that adds a "/" after directory names (such as tcsh and
   bash), because on symlinks to directories, several system calls
   have different semantics according to whether a trailing slash is
   present.  */

bool
strip_trailing_slashes (char *file)
{
  char *base = last_component (file);
  char *base_lim;
  bool had_slash;

  /* last_component returns "" for file system roots, but we need to turn
     `///' into `/'.  */
  if (! *base)
    base = file;
  base_lim = base + base_len (base);
  had_slash = (*base_lim != '\0');
  *base_lim = '\0';
  return had_slash;
}
