

/* written by Jim Meyering */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

/* Disable the definitions of these functions (from config.h)
   so we can use the library versions here.  */
#undef gettimeofday
#undef gmtime
#undef localtime
#undef tzset

#include <sys/types.h>

#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

#include <stdlib.h>

static struct tm *localtime_buffer_addr;

/* This is a wrapper for localtime.  It is used only on systems for which
   gettimeofday clobbers the static buffer used for localtime's result.

   On the first call, record the address of the static buffer that
   localtime uses for its result.  */

struct tm *
rpl_localtime (const time_t *timep)
{
  struct tm *tm = localtime (timep);

  if (! localtime_buffer_addr)
    localtime_buffer_addr = tm;

  return tm;
}

/* Same as above, since gmtime and localtime use the same buffer.  */
struct tm *
rpl_gmtime (const time_t *timep)
{
  struct tm *tm = gmtime (timep);

  if (! localtime_buffer_addr)
    localtime_buffer_addr = tm;

  return tm;
}

/* This is a wrapper for gettimeofday.  It is used only on systems for which
   gettimeofday clobbers the static buffer used for localtime's result.

   Save and restore the contents of the buffer used for localtime's result
   around the call to gettimeofday.  */

int
rpl_gettimeofday (struct timeval *tv, struct timezone *tz)
{
  struct tm save;
  int result;

  if (! localtime_buffer_addr)
    {
      time_t t = 0;
      localtime_buffer_addr = localtime (&t);
    }

  save = *localtime_buffer_addr;
  result = gettimeofday (tv, tz);
  *localtime_buffer_addr = save;

  return result;
}

/* This is a wrapper for tzset. It is used only on systems for which
   tzset may clobber the static buffer used for localtime's result.
   Save and restore the contents of the buffer used for localtime's
   result around the call to tzset.  */
void
rpl_tzset (void)
{
  struct tm save;

  if (! localtime_buffer_addr)
    {
      time_t t = 0;
      localtime_buffer_addr = localtime (&t);
    }

  save = *localtime_buffer_addr;
  tzset ();
  *localtime_buffer_addr = save;
}
