

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#define ARGP_FS_EI
#undef __OPTIMIZE__
#define __OPTIMIZE__ 1
#include "argp-fmtstream.h"

#if 0
/* Not exported.  */
/* Add weak aliases.  */
#if _LIBC - 0 && !defined (ARGP_FMTSTREAM_USE_LINEWRAP) && defined (weak_alias)

weak_alias (__argp_fmtstream_putc, argp_fmtstream_putc)
weak_alias (__argp_fmtstream_puts, argp_fmtstream_puts)
weak_alias (__argp_fmtstream_write, argp_fmtstream_write)
weak_alias (__argp_fmtstream_set_lmargin, argp_fmtstream_set_lmargin)
weak_alias (__argp_fmtstream_set_rmargin, argp_fmtstream_set_rmargin)
weak_alias (__argp_fmtstream_set_wmargin, argp_fmtstream_set_wmargin)
weak_alias (__argp_fmtstream_point, argp_fmtstream_point)

#endif
#endif
