

#pragma once

#include "threads/platform/Condition.h"

#include "threads/SystemClock.h"
#include <stdio.h>

namespace XbmcThreads
{

  /**
   * This is a condition variable along with its predicate. This allows the use of a 
   *  condition variable without the spurious returns since the state being monitored
   *  is also part of the condition.
   *
   * L should implement the Lockable concept
   *
   * The requirements on P are that it can act as a predicate (that is, I can use
   *  it in an 'while(!predicate){...}' where 'predicate' is of type 'P').
   */
  template <typename P> class TightConditionVariable
  {
    ConditionVariable& cond;
    P predicate;

  public:
    inline TightConditionVariable(ConditionVariable& cv, P predicate_) : cond(cv), predicate(predicate_) {}

    template <typename L> inline void wait(L& lock) { while(!predicate) cond.wait(lock); }
    template <typename L> inline bool wait(L& lock, unsigned long milliseconds)
    {
      bool ret = true;
      if (!predicate)
      {
        if (!milliseconds)
        {
          cond.wait(lock,milliseconds /* zero */);
          return !(!predicate); // eh? I only require the ! operation on P
        }
        else
        {
          EndTime endTime((unsigned int)milliseconds);
          for (bool notdone = true; notdone && ret == true;
               ret = (notdone = (!predicate)) ? ((milliseconds = endTime.MillisLeft()) != 0) : true)
            cond.wait(lock,milliseconds);
        }
      }
      return ret;
    }

    inline void notifyAll() { cond.notifyAll(); }
    inline void notify() { cond.notify(); }
  };
}

