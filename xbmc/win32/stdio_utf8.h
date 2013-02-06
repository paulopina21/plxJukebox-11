

#ifndef STDIO_UTF8_H__
#define STDIO_UTF8_H__

#include <cstdio>

extern int   remove_utf8(const char* __filename);
extern int   rename_utf8(const char* __old, const char* __new);
extern FILE* fopen64_utf8(const char* __filename, const char* __modes);

#endif // STDIO_UTF8_H__

