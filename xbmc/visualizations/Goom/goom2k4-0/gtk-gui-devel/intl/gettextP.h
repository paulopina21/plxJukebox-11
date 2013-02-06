

#ifndef _GETTEXTP_H
#define _GETTEXTP_H

#include "loadinfo.h"

/* @@ end of prolog @@ */

#ifndef PARAMS
# if __STDC__
#  define PARAMS(args) args
# else
#  define PARAMS(args) ()
# endif
#endif

#ifndef internal_function
# define internal_function
#endif

#ifndef W
# define W(flag, data) ((flag) ? SWAP (data) : (data))
#endif


#ifdef _LIBC
# include <byteswap.h>
# define SWAP(i) bswap_32 (i)
#else
static nls_uint32 SWAP PARAMS ((nls_uint32 i));

static inline nls_uint32
SWAP (i)
     nls_uint32 i;
{
  return (i << 24) | ((i & 0xff00) << 8) | ((i >> 8) & 0xff00) | (i >> 24);
}
#endif


struct loaded_domain
{
  const char *data;
  int use_mmap;
  size_t mmap_size;
  int must_swap;
  nls_uint32 nstrings;
  struct string_desc *orig_tab;
  struct string_desc *trans_tab;
  nls_uint32 hash_size;
  nls_uint32 *hash_tab;
};

struct binding
{
  struct binding *next;
  char *domainname;
  char *dirname;
};

struct loaded_l10nfile *_nl_find_domain PARAMS ((const char *__dirname,
						 char *__locale,
						 const char *__domainname))
     internal_function;
void _nl_load_domain PARAMS ((struct loaded_l10nfile *__domain))
     internal_function;
void _nl_unload_domain PARAMS ((struct loaded_domain *__domain))
     internal_function;

/* @@ begin of epilog @@ */

#endif /* gettextP.h  */
