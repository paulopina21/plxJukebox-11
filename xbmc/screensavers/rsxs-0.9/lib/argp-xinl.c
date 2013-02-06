

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#if defined _LIBC || defined HAVE_FEATURES_H
# include <features.h>
#endif

#ifndef __USE_EXTERN_INLINES
# define __USE_EXTERN_INLINES	1
#endif
#define ARGP_EI
#undef __OPTIMIZE__
#define __OPTIMIZE__ 1
#include "argp.h"

/* Add weak aliases.  */
#if _LIBC - 0 && defined (weak_alias)

weak_alias (__argp_usage, argp_usage)
weak_alias (__option_is_short, _option_is_short)
weak_alias (__option_is_end, _option_is_end)

#endif
