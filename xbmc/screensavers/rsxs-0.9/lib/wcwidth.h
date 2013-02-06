

#ifndef _gl_WCWIDTH_H
#define _gl_WCWIDTH_H

#if HAVE_WCHAR_T

/* Get wcwidth if available, along with wchar_t.  */
# if HAVE_WCHAR_H
/* Tru64 with Desktop Toolkit C has a bug: <stdio.h> must be included before
   <wchar.h>.
   BSD/OS 4.1 has a bug: <stdio.h> and <time.h> must be included before
   <wchar.h>.  */
#  include <stdio.h>
#  include <time.h>
#  include <wchar.h>
# endif

/* Get iswprint.  */
# if HAVE_WCTYPE_H
#  include <wctype.h>
# endif
# if !defined iswprint && !HAVE_ISWPRINT
#  define iswprint(wc) 1
# endif

# ifndef HAVE_DECL_WCWIDTH
"this configure-time declaration test was not run"
# endif
# ifndef wcwidth
#  if !HAVE_WCWIDTH

/* wcwidth doesn't exist, so assume all printable characters have
   width 1.  */
static inline int
wcwidth (wchar_t wc)
{
  return wc == 0 ? 0 : iswprint (wc) ? 1 : -1;
}

#  elif !HAVE_DECL_WCWIDTH

/* wcwidth exists but is not declared.  */
extern
#   ifdef __cplusplus
"C"
#   endif
int wcwidth (int /* actually wchar_t */);

#  endif
# endif

#endif /* HAVE_WCHAR_H */

#endif /* _gl_WCWIDTH_H */
