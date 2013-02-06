#pragma once



#include <stdint.h>

class CStopWatch
{
public:
  CStopWatch(bool useFrameTime=false);
  ~CStopWatch();

  bool IsRunning() const;
  void StartZero();          ///< Resets clock to zero and starts running
  void Start();              ///< Sets clock to zero if not running and starts running.
  void Stop();               ///< Stops clock and sets to zero if running.
  void Reset();              ///< Resets clock to zero - does not alter running state.

  float GetElapsedSeconds() const;
  float GetElapsedMilliseconds() const;
private:
  int64_t GetTicks() const;
  float m_timerPeriod;        // to save division in GetElapsed...()
  int64_t m_startTick;
  bool m_isRunning;
  bool m_useFrameTime;
};
