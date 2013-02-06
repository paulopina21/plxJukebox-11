

#pragma once

#include <boost/thread/thread.hpp>

#define BOOST_MILLIS(x) (boost::get_system_time() + boost::posix_time::milliseconds(x))

inline static void Sleep(unsigned int millis) { boost::thread::sleep(BOOST_MILLIS(millis)); }

template<class E> inline static bool waitForWaiters(E& event, int numWaiters, int milliseconds)
{
  for( int i = 0; i < milliseconds; i++)
  {
    if (event.getNumWaits() == numWaiters)
      return true;
    Sleep(1);
  }
  return false;
}
  
inline static bool waitForThread(volatile long& mutex, int numWaiters, int milliseconds)
{
  CCriticalSection sec;
  for( int i = 0; i < milliseconds; i++)
  {
    if (mutex == (long)numWaiters)
      return true;

    {
      CSingleLock tmplock(sec); // kick any memory syncs
    }
    Sleep(1);
  }
  return false;
}

class AtomicGuard
{
  volatile long* val;
public:
  inline AtomicGuard(volatile long* val_) : val(val_) { if (val) AtomicIncrement(val); }
  inline ~AtomicGuard() { if (val) AtomicDecrement(val); }
};

