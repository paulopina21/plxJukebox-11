

#pragma once

#include <pthread.h>
#include <errno.h>

#include "threads/Lockables.h"
#include "threads/Helpers.h"

namespace XbmcThreads
{

  // forward declare in preparation for the friend declaration
  class ConditionVariable;

  namespace pthreads
  {
    class RecursiveMutex
    {
      pthread_mutexattr_t* getRecursiveAttr();
      pthread_mutex_t mutex;

      // needs acces to 'mutex'
      friend class XbmcThreads::ConditionVariable;
    public:
      inline RecursiveMutex() { pthread_mutex_init(&mutex,getRecursiveAttr()); }
      
      inline ~RecursiveMutex() { pthread_mutex_destroy(&mutex); }

      inline void lock() { pthread_mutex_lock(&mutex); }

      inline void unlock() { pthread_mutex_unlock(&mutex); }
        
      inline bool try_lock() { return (pthread_mutex_trylock(&mutex) == 0); }
    };
  }
}


/**
 * A CCriticalSection is a CountingLockable whose implementation is a 
 *  native recursive mutex.
 *
 * This is not a typedef because of a number of "class CCriticalSection;" 
 *  forward declarations in the code that break when it's done that way.
 */
class CCriticalSection : public XbmcThreads::CountingLockable<XbmcThreads::pthreads::RecursiveMutex> {};

