
/**
 * $Id: wipemalloc.c,v 1.1.1.1 2005/12/23 18:05:05 psperl Exp $
 *
 * Clean memory allocator
 */

#include "wipemalloc.h"

 void *wipemalloc( size_t count ) {
    void *mem = malloc( count );
    if ( mem != NULL ) {
        memset( mem, 0, count );
      } else {
        printf( "wipemalloc() failed to allocate %d bytes\n", (int)count );
      }
    return mem;
  }

/** Safe memory deallocator */
 void wipefree( void *ptr ) {
    if ( ptr != NULL ) {
        free( ptr );
      }
  }
