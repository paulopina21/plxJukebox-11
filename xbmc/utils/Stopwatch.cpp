

#include "threads/SystemClock.h"
#include "Stopwatch.h"
#if defined(_LINUX) && !defined(__APPLE__) && !defined(__FreeBSD__)
#include <sys/sysinfo.h>
#endif
#include "utils/TimeUtils.h"

CStopWatch::CStopWatch(bool useFrameTime /*=false*/)
{
  m_timerPeriod      = 0.0f;
  m_startTick        = 0;
  m_isRunning        = false;
  m_useFrameTime     = useFrameTime;

  if (m_useFrameTime)
  {
    m_timerPeriod = 1.0f / 1000.0f; //frametime is in milliseconds
  }
  else
  {
  // Get the timer frequency (ticks per second)
#ifndef _LINUX
  m_timerPeriod = 1.0f / (float)CurrentHostFrequency();
#else
  m_timerPeriod = 1.0f / 1000.0f; // we want seconds
#endif
  }
}

CStopWatch::~CStopWatch()
{
}

bool CStopWatch::IsRunning() const
{
  return m_isRunning;
}

void CStopWatch::StartZero()
{
  m_startTick = GetTicks();
  m_isRunning = true;
}

void CStopWatch::Start()
{
  if (!m_isRunning)
    m_startTick = GetTicks();
  m_isRunning = true;
}

void CStopWatch::Stop()
{
  if( m_isRunning )
  {
    m_startTick = 0;
    m_isRunning = false;
  }
}

void CStopWatch::Reset()
{
  if (m_isRunning)
    m_startTick = GetTicks();
}

float CStopWatch::GetElapsedSeconds() const
{
  int64_t totalTicks = m_isRunning ? (GetTicks() - m_startTick) : 0;
  return (float)totalTicks * m_timerPeriod;
}

float CStopWatch::GetElapsedMilliseconds() const
{
  return GetElapsedSeconds() * 1000.0f;
}

int64_t CStopWatch::GetTicks() const
{
  if (m_useFrameTime)
    return CTimeUtils::GetFrameTime();
#ifndef _LINUX
  return CurrentHostCounter();
#else
  return XbmcThreads::SystemClockMillis();
#endif
}
