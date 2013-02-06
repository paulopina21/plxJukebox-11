

#include "threads/Lockables.h"
#include "threads/platform/pthreads/CriticalSection.h"
#include "threads/Helpers.h"

#include <pthread.h>

namespace XbmcThreads
{
  namespace pthreads
  {
    // ==========================================================
    static pthread_mutexattr_t recursiveAttr;

    static bool setRecursiveAttr() 
    {
      static bool alreadyCalled = false; // initialized to 0 in the data segment prior to startup init code running
      if (!alreadyCalled)
      {
        pthread_mutexattr_init(&recursiveAttr);
        pthread_mutexattr_settype(&recursiveAttr,PTHREAD_MUTEX_RECURSIVE);
        alreadyCalled = true;
      }
      return true; // note, we never call destroy.
    }

    static bool recursiveAttrSet = setRecursiveAttr();

    pthread_mutexattr_t* RecursiveMutex::getRecursiveAttr()
    {
      if (!recursiveAttrSet) // this is only possible in the single threaded startup code
        recursiveAttrSet = setRecursiveAttr();
      return &recursiveAttr;
    }
    // ==========================================================
  }
}

