

#ifndef VSNPRINTF_H
#define VSNPRINTF_H

#include <stdarg.h>

/* Get vsnprintf declaration, if available.  */
#include <stdio.h>

#if defined HAVE_DECL_VSNPRINTF && !HAVE_DECL_VSNPRINTF
int vsnprintf (char *str, size_t size, const char *format, va_list args);
#endif

#endif /* VSNPRINTF_H */
