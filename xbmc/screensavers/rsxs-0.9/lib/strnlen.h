

#ifndef STRNLEN_H
#define STRNLEN_H

/* Get strnlen declaration, if available.  */
#include <string.h>

#if defined HAVE_DECL_STRNLEN && !HAVE_DECL_STRNLEN
/* Find the length (number of bytes) of STRING, but scan at most
   MAXLEN bytes.  If no '\0' terminator is found in that many bytes,
   return MAXLEN.  */
extern size_t strnlen(const char *string, size_t maxlen);
#endif

#endif /* STRNLEN_H */
