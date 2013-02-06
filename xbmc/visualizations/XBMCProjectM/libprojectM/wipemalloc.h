
/**
 * $Id: wipemalloc.h,v 1.1.1.1 2005/12/23 18:05:03 psperl Exp $
 *
 * Contains an inline function which can replace malloc() that also 
 * call memset( ..., 0, sizeof( ... ) ) on the allocated block for
 * safe initialization
 *
 * $Log$
 */

#ifndef _WIPEMALLOC_H
#define _WIPEMALLOC_H

#ifndef MACOS
#ifndef HAVE_AIX /** AIX has malloc() defined in a strange place... */
#ifdef WIN32
#include <malloc.h>
#endif
#include <string.h>
#include <stdlib.h>
#else
#include <stdlib.h>
#endif /** !HAVE_AIX */
#else
#include <string.h>
#include <stdlib.h>
#endif /** !MACOS */
#include <stdio.h>

#ifdef PANTS
#if defined(WIN32) && !defined(inline)
#define inline
#endif
#endif

/** Safe memory allocator */
 void *wipemalloc( size_t count );
 void wipefree( void *ptr );

#endif /** !_WIPEMALLOC_H */
