

#pragma once

#include "threads/SingleLock.h"
#include "threads/Helpers.h"

#include <pthread.h>
#include <sys/time.h>
#include <assert.h>

namespace XbmcThreads
{

  /**
   * This is a thin wrapper around boost::condition_variable. It is subject
   *  to "spurious returns" as it is built on boost which is built on posix
   *  on many of our platforms.
   */
  class ConditionVariable : public NonCopyable
  {
  private:
    pthread_cond_t cond;

  public:
    inline ConditionVariable() 
    { 
      pthread_cond_init(&cond,NULL); 
    }

    inline ~ConditionVariable() 
    { 
      pthread_cond_destroy(&cond);
    }

    inline void wait(CCriticalSection& lock) 
    { 
      pthread_cond_wait(&cond,&lock.get_underlying().mutex);
    }

    inline bool wait(CCriticalSection& lock, unsigned long milliseconds) 
    { 
      struct timeval tv;
      struct timespec ts;

      gettimeofday(&tv,NULL);

      milliseconds += tv.tv_usec / 1000; // move the usecs onto milliseconds

      time_t tsecs = (time_t)(milliseconds/1000); // temporary used for assert
      assert(tsecs >= (time_t)0);

      ts.tv_sec = tv.tv_sec + tsecs;
      ts.tv_nsec = (long)((milliseconds % (unsigned long)1000) * (unsigned long)1000000);
      return (pthread_cond_timedwait(&cond,&lock.get_underlying().mutex,&ts) == 0);
    }

    inline void wait(CSingleLock& lock) { wait(lock.get_underlying()); }
    inline bool wait(CSingleLock& lock, unsigned long milliseconds) { return wait(lock.get_underlying(), milliseconds); }

    inline void notifyAll() 
    { 
      pthread_cond_broadcast(&cond);
    }

    inline void notify() 
    { 
      pthread_cond_signal(&cond);
    }
  };

}
