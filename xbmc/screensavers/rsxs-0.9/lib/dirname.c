

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "dirname.h"

#include <string.h>
#include "xalloc.h"

/* Return the length of the prefix of FILE that will be used by
   dir_name.  If FILE is in the working directory, this returns zero
   even though `dir_name (FILE)' will return ".".  Works properly even
   if there are trailing slashes (by effectively ignoring them).  */

size_t
dir_len (char const *file)
{
  size_t prefix_length = FILE_SYSTEM_PREFIX_LEN (file);
  size_t length;

  /* Advance prefix_length beyond important leading slashes.  */
  prefix_length += (prefix_length != 0
		    ? (FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE
		       && ISSLASH (file[prefix_length]))
		    : (ISSLASH (file[0])
		       ? ((DOUBLE_SLASH_IS_DISTINCT_ROOT
			   && ISSLASH (file[1]) && ! ISSLASH (file[2])
			   ? 2 : 1))
		       : 0));

  /* Strip the basename and any redundant slashes before it.  */
  for (length = last_component (file) - file;
       prefix_length < length; length--)
    if (! ISSLASH (file[length - 1]))
      break;
  return length;
}


/* In general, we can't use the builtin `dirname' function if available,
   since it has different meanings in different environments.
   In some environments the builtin `dirname' modifies its argument.

   Return the leading directories part of FILE, allocated with xmalloc.
   Works properly even if there are trailing slashes (by effectively
   ignoring them).  Unlike POSIX dirname(), FILE cannot be NULL.

   If lstat (FILE) would succeed, then { chdir (dir_name (FILE));
   lstat (base_name (FILE)); } will access the same file.  Likewise,
   if the sequence { chdir (dir_name (FILE));
   rename (base_name (FILE), "foo"); } succeeds, you have renamed FILE
   to "foo" in the same directory FILE was in.  */

char *
dir_name (char const *file)
{
  size_t length = dir_len (file);
  bool append_dot = (length == 0
		     || (FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE
			 && length == FILE_SYSTEM_PREFIX_LEN (file)
			 && file[2] != '\0' && ! ISSLASH (file[2])));
  char *dir = xmalloc (length + append_dot + 1);
  memcpy (dir, file, length);
  if (append_dot)
    dir[length++] = '.';
  dir[length] = '\0';
  return dir;
}
