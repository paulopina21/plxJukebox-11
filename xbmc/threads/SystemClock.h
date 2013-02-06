

#pragma once

#include <limits>

namespace XbmcThreads
{
  /**
   * This function returns the system clock's number of milliseconds but with
   *  an arbitrary reference point. It handles the wrapping of any underlying
   *  system clock by setting a starting point at the first call. It should
   *  only be used for measuring time durations.
   *
   * Of course, on windows it just calls timeGetTime, so you're on your own.
   */
  unsigned int SystemClockMillis();

  /**
   * DO NOT compare the results from SystemClockMillis() to an expected end time
   *  that was calculated by adding a number of milliseconds to some start time.
   *  The reason is becuse the SystemClockMillis could wrap. Instead use this
   *  class which uses differences (which are safe accross a wrap).
   */
  class EndTime
  {
    unsigned int startTime;
    unsigned int totalWaitTime;
  public:
    inline EndTime() : startTime(0), totalWaitTime(0) {}
    inline EndTime(unsigned int millisecondsIntoTheFuture) : startTime(SystemClockMillis()), totalWaitTime(millisecondsIntoTheFuture) {}

    inline void Set(unsigned int millisecondsIntoTheFuture) { startTime = SystemClockMillis(); totalWaitTime = millisecondsIntoTheFuture; }

    inline bool IsTimePast() { return totalWaitTime == 0 ? true : (SystemClockMillis() - startTime) >= totalWaitTime; }

    inline unsigned int MillisLeft()
    {
      unsigned int timeWaitedAlready = (SystemClockMillis() - startTime);
      return (timeWaitedAlready >= totalWaitTime) ? 0 : (totalWaitTime - timeWaitedAlready);
    }

    inline void SetExpired() { totalWaitTime = 0; }
    inline void SetInfinite() { totalWaitTime = std::numeric_limits<unsigned int>::max(); }
  };
}
