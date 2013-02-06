

#ifndef _STRCASE_H
#define _STRCASE_H

#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif


/* Compare strings S1 and S2, ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less than, equal to or greater
   than S2.
   Note: This function may, in multibyte locales, return 0 for strings of
   different lengths!  */
extern int strcasecmp (const char *s1, const char *s2);

/* Compare no more than N characters of strings S1 and S2, ignoring case,
   returning less than, equal to or greater than zero if S1 is
   lexicographically less than, equal to or greater than S2.
   Note: This function can not work correctly in multibyte locales.  */
extern int strncasecmp (const char *s1, const char *s2, size_t n);


#ifdef __cplusplus
}
#endif


#endif /* _STRCASE_H */
