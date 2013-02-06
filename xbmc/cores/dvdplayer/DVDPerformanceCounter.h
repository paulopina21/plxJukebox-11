#pragma once



#define FILETIME_TO_ULARGE_INTEGER(ularge, filetime) { ularge.u.HighPart = filetime.dwHighDateTime; ularge.u.LowPart = filetime.dwLowDateTime; }

#include "system.h"

#include "threads/SingleLock.h"

class CDVDMessageQueue;

typedef struct stProcessPerformance
{
  ULARGE_INTEGER  timer_thread;
  ULARGE_INTEGER  timer_system;
  HANDLE          hThread;
} ProcessPerformance;

class CDVDPerformanceCounter
{
public:
  CDVDPerformanceCounter();
  ~CDVDPerformanceCounter();

  bool Initialize();
  void DeInitialize();

  void EnableAudioQueue(CDVDMessageQueue* pQueue)   { CSingleLock lock(m_critSection); m_pAudioQueue = pQueue; }
  void DisableAudioQueue()                          { CSingleLock lock(m_critSection); m_pAudioQueue = NULL;  }

  void EnableVideoQueue(CDVDMessageQueue* pQueue)   { CSingleLock lock(m_critSection); m_pVideoQueue = pQueue;  }
  void DisableVideoQueue()                          { CSingleLock lock(m_critSection); m_pVideoQueue = NULL;  }

  void EnableVideoDecodePerformance(HANDLE hThread) { CSingleLock lock(m_critSection); m_videoDecodePerformance.hThread = hThread;  }
  void DisableVideoDecodePerformance()              { CSingleLock lock(m_critSection); m_videoDecodePerformance.hThread = NULL;  }

  void EnableAudioDecodePerformance(HANDLE hThread) { CSingleLock lock(m_critSection); m_audioDecodePerformance.hThread = hThread;  }
  void DisableAudioDecodePerformance()              { CSingleLock lock(m_critSection); m_audioDecodePerformance.hThread = NULL;  }

  void EnableMainPerformance(HANDLE hThread)        { CSingleLock lock(m_critSection); m_mainPerformance.hThread = hThread;  }
  void DisableMainPerformance()                     { CSingleLock lock(m_critSection); m_mainPerformance.hThread = NULL;  }

  CDVDMessageQueue*         m_pAudioQueue;
  CDVDMessageQueue*         m_pVideoQueue;

  ProcessPerformance        m_videoDecodePerformance;
  ProcessPerformance        m_audioDecodePerformance;
  ProcessPerformance        m_mainPerformance;

private:
  CCriticalSection m_critSection;
};

extern CDVDPerformanceCounter g_dvdPerformanceCounter;

