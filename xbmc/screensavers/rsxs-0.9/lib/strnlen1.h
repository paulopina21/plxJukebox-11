

#ifndef _STRNLEN1_H
#define _STRNLEN1_H

#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif


/* Find the length of STRING + 1, but scan at most MAXLEN bytes.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
/* This is the same as strnlen (string, maxlen - 1) + 1.  */
extern size_t strnlen1 (const char *string, size_t maxlen);


#ifdef __cplusplus
}
#endif


#endif /* _STRNLEN1_H */
