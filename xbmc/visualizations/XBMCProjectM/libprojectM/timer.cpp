
/**
 * $Id: timer.c,v 1.1.1.1 2005/12/23 18:05:05 psperl Exp $
 *
 * Platform-independent timer
 */

#include "timer.h"
#include <stdlib.h>

#ifndef WIN32
/** Get number of ticks since the given timestamp */
unsigned int getTicks( struct timeval *start ) {
    struct timeval now;
    unsigned int ticks;

    gettimeofday(&now, NULL);
    ticks=(now.tv_sec-start->tv_sec)*1000+(now.tv_usec-start->tv_usec)/1000;
    return(ticks);
  }

#else
unsigned int getTicks( long start ) {
    return GetTickCount() - start;
  }

#endif /** !WIN32 */


  
