

#ifndef _GETTEXT_H
#define _GETTEXT_H 1

#include <stdio.h>

#if HAVE_LIMITS_H || _LIBC
# include <limits.h>
#endif

/* @@ end of prolog @@ */


#define _MAGIC 0x950412de
#define _MAGIC_SWAPPED 0xde120495

/* Revision number of the currently used .mo (binary) file format.  */
#define MO_REVISION_NUMBER 0

/* The following contortions are an attempt to use the C preprocessor
   to determine an unsigned integral type that is 32 bits wide.  An
   alternative approach is to use autoconf's AC_CHECK_SIZEOF macro, but
   doing that would require that the configure script compile and *run*
   the resulting executable.  Locally running cross-compiled executables
   is usually not possible.  */

#if __STDC__
# define UINT_MAX_32_BITS 4294967295U
#else
# define UINT_MAX_32_BITS 0xFFFFFFFF
#endif



#ifndef UINT_MAX
# define UINT_MAX UINT_MAX_32_BITS
#endif

#if UINT_MAX == UINT_MAX_32_BITS
typedef unsigned nls_uint32;
#else
# if USHRT_MAX == UINT_MAX_32_BITS
typedef unsigned short nls_uint32;
# else
#  if ULONG_MAX == UINT_MAX_32_BITS
typedef unsigned long nls_uint32;
#  else
  /* The following line is intended to throw an error.  Using #error is
     not portable enough.  */
  "Cannot determine unsigned 32-bit data type."
#  endif
# endif
#endif


/* Header for binary .mo file format.  */
struct mo_file_header
{
  /* The magic number.  */
  nls_uint32 magic;
  /* The revision number of the file format.  */
  nls_uint32 revision;
  /* The number of strings pairs.  */
  nls_uint32 nstrings;
  /* Offset of table with start offsets of original strings.  */
  nls_uint32 orig_tab_offset;
  /* Offset of table with start offsets of translation strings.  */
  nls_uint32 trans_tab_offset;
  /* Size of hashing table.  */
  nls_uint32 hash_tab_size;
  /* Offset of first hashing entry.  */
  nls_uint32 hash_tab_offset;
};

struct string_desc
{
  /* Length of addressed string.  */
  nls_uint32 length;
  /* Offset of string in file.  */
  nls_uint32 offset;
};

/* @@ begin of epilog @@ */

#endif	/* gettext.h  */
