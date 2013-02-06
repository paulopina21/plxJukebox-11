

#include "system.h"
#include "PerformanceSample.h"

#ifdef _LINUX
#include "linux/PlatformInclude.h"
#endif

#include "Application.h"
#include "log.h"
#include "TimeUtils.h"

using namespace std;

int64_t CPerformanceSample::m_tmFreq;

CPerformanceSample::CPerformanceSample(const string &statName, bool bCheckWhenDone)
{
  m_statName = statName;
  m_bCheckWhenDone = bCheckWhenDone;
  if (m_tmFreq == 0LL)
    m_tmFreq = CurrentHostFrequency();

  Reset();
}

CPerformanceSample::~CPerformanceSample()
{
  if (m_bCheckWhenDone)
    CheckPoint();
}

void CPerformanceSample::Reset()
{
  m_tmStart = CurrentHostCounter();
#ifdef _LINUX
  if (getrusage(RUSAGE_SELF, &m_usage) == -1)
    CLog::Log(LOGERROR,"error %d in getrusage", errno);
#endif
}

void CPerformanceSample::CheckPoint()
{
#ifdef HAS_PERFORMANCE_SAMPLE
  int64_t tmNow;
  tmNow = CurrentHostCounter();
  double elapsed = (double)(tmNow - m_tmStart) / (double)m_tmFreq.QuadPart;

  double dUser=0.0, dSys=0.0;
#ifdef _LINUX
  struct rusage usage;
  if (getrusage(RUSAGE_SELF, &usage) == -1)
    CLog::Log(LOGERROR,"error %d in getrusage", errno);
  else
  {
    dUser = ( ((double)usage.ru_utime.tv_sec + (double)usage.ru_utime.tv_usec / 1000000.0) -
              ((double)m_usage.ru_utime.tv_sec + (double)m_usage.ru_utime.tv_usec / 1000000.0) );
    dSys  = ( ((double)usage.ru_stime.tv_sec + (double)usage.ru_stime.tv_usec / 1000000.0) -
              ((double)m_usage.ru_stime.tv_sec + (double)m_usage.ru_stime.tv_usec / 1000000.0) );
  }
#endif

  g_application.GetPerformanceStats().AddSample(m_statName, PerformanceCounter(elapsed,dUser,dSys));
#endif

  Reset();
}

double CPerformanceSample::GetEstimatedError()
{
  if (m_tmFreq == 0LL)
    m_tmFreq = CurrentHostFrequency();

  int64_t tmStart, tmEnd;
  tmStart = CurrentHostCounter();

  for (int i=0; i<100000;i++)
  {
    DECLARE_UNUSED(int64_t,tmDummy);
    tmDummy = CurrentHostCounter();
  }

  tmEnd = CurrentHostCounter();
  double elapsed = (double)(tmEnd - tmStart) / (double)m_tmFreq;

  return (elapsed / 100000.0) * 2.0; // one measure at start time and another when done.
}




