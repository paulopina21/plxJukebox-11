

#pragma once

#include "threads/Lockables.h"

#include <windows.h>

namespace XbmcThreads
{

  namespace intern
  {
    // forward declare in preparation for the friend declaration
    class ConditionVariableVista;
    class ConditionVariableXp;
  }

  namespace windows
  {
    class RecursiveMutex
    {
      CRITICAL_SECTION mutex;

      // needs acces to 'mutex'
      friend class XbmcThreads::intern::ConditionVariableVista;
      friend class XbmcThreads::intern::ConditionVariableXp;
    public:
      inline RecursiveMutex()
      {
        InitializeCriticalSection(&mutex);
      }
      
      inline ~RecursiveMutex()
      {
        DeleteCriticalSection(&mutex);
      }

      inline void lock()
      {
        EnterCriticalSection(&mutex);
      }

      inline void unlock()
      {
        LeaveCriticalSection(&mutex);
      }
        
      inline bool try_lock()
      {
        return TryEnterCriticalSection(&mutex) ? true : false;
      }
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
class CCriticalSection : public XbmcThreads::CountingLockable<XbmcThreads::windows::RecursiveMutex> {};

