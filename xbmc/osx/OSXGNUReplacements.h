#ifndef __OSXPLATFORM_H__
#define __OSXPLATFORM_H__


// This is a catch all for GNU routines that do not exist under OSX.
#include <netdb.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

size_t strnlen(const char *s, size_t n);
char* strndup(char const *s, size_t n);
int gethostbyname_r(const char *name, struct hostent *ret, char *buf,
    size_t buflen, struct hostent **result, int *h_errnop);

#ifdef __cplusplus
}
#endif /* __cplusplus */
    


/* Written by Simon Josefsson. */
# include <stddef.h>
# include <stdio.h>
# include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

ssize_t getdelim(char **lineptr, size_t *n, int delimiter, FILE *stream);
ssize_t getline (char **lineptr, size_t *n, FILE *stream);
int strverscmp (const char *s1, const char *s2);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
