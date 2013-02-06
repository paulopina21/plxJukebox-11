
#ifndef _SCHED_H
#define _SCHED_H

#if defined(__MINGW32__) || defined(_UWIN)
/* For pid_t */
#  include <sys/types.h>
/* Required by Unix 98 */
#  include <time.h>
#else
typedef int pid_t;
#endif

/* Thread scheduling policies */

enum {
  SCHED_OTHER = 0,
  SCHED_FIFO,
  SCHED_RR,
  SCHED_MIN   = SCHED_OTHER,
  SCHED_MAX   = SCHED_RR
};

struct sched_param {
  int sched_priority;
};

#ifdef __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

int sched_yield (void);

int sched_get_priority_min (int policy);

int sched_get_priority_max (int policy);

int sched_setscheduler (pid_t pid, int policy);

int sched_getscheduler (pid_t pid);

/*
 * Note that this macro returns ENOTSUP rather than
 * ENOSYS as might be expected. However, returning ENOSYS
 * should mean that sched_get_priority_{min,max} are
 * not implemented as well as sched_rr_get_interval.
 * This is not the case, since we just don't support
 * round-robin scheduling. Therefore I have chosen to
 * return the same value as sched_setscheduler when
 * SCHED_RR is passed to it.
 */
#define sched_rr_get_interval(_pid, _interval) \
  ( errno = ENOTSUP, (int) -1 )


#ifdef __cplusplus
}                               /* End of extern "C" */
#endif                          /* __cplusplus */


#endif                          /* !_SCHED_H */

