

#if !defined(LT__ARGZ_H)
#define LT__ARGZ_H 1

#include <stdlib.h>
#include <sys/types.h>

#if defined(LTDL)
#  include "lt__glibc.h"
#  include "lt_system.h"
#else
#  define LT_SCOPE
#endif

#if defined(_cplusplus)
extern "C" {
#endif

LT_SCOPE error_t argz_append	(char **pargz, size_t *pargz_len,
				 const char *buf, size_t buf_len);
LT_SCOPE error_t argz_create_sep(const char *str, int delim,
				 char **pargz, size_t *pargz_len);
LT_SCOPE error_t argz_insert	(char **pargz, size_t *pargz_len,
				 char *before, const char *entry);
LT_SCOPE char *	 argz_next	(char *argz, size_t argz_len,
				 const char *entry);
LT_SCOPE void	 argz_stringify	(char *argz, size_t argz_len, int sep);

#if defined(_cplusplus)
}
#endif

#if !defined(LTDL)
#  undef LT_SCOPE
#endif

#endif /*!defined(LT__ARGZ_H)*/
