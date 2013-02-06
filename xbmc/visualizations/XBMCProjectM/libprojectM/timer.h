
/**
 * $Id: timer.h,v 1.1.1.1 2005/12/23 18:05:00 psperl Exp $
 *
 * Platform-independent timer
 *
 * $Log: timer.h,v $
 * Revision 1.1.1.1  2005/12/23 18:05:00  psperl
 * Imported
 *
 * Revision 1.2  2004/10/05 09:19:40  cvs
 * Fixed header include defines
 *
 * Revision 1.1.1.1  2004/10/04 12:56:00  cvs
 * Imported
 *
 */

#ifndef _TIMER_H
#define _TIMER_H

#ifndef WIN32
#include <sys/time.h>
unsigned int getTicks( struct timeval *start );
struct timeval GetCurrentTime();
#else
#include <windows.h>
unsigned int getTicks( long start );

#endif /** !WIN32 */

#endif /** _TIMER_H */
