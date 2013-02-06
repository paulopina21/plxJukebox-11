


#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <limits.h>

#include "mbchar.h"

#if IS_BASIC_ASCII

/* Bit table of characters in the ISO C "basic character set".  */
unsigned int is_basic_table [UCHAR_MAX / 32 + 1] =
{
  0x00001a00,		/* '\t' '\v' '\f' */
  0xffffffef,		/* ' '...'#' '%'...'?' */
  0xfffffffe,		/* 'A'...'Z' '[' '\\' ']' '^' '_' */
  0x7ffffffe		/* 'a'...'z' '{' '|' '}' '~' */
  /* The remaining bits are 0.  */
};

#endif /* IS_BASIC_ASCII */
