

#include "InfoLoader.h"
#include "guilib/LocalizeStrings.h"
#include "JobManager.h"
#include "TimeUtils.h"

CInfoLoader::CInfoLoader(unsigned int timeToRefresh)
{
  m_refreshTime = 0;
  m_timeToRefresh = timeToRefresh;
  m_busy = false;
}

CInfoLoader::~CInfoLoader()
{
}

void CInfoLoader::OnJobComplete(unsigned int jobID, bool success, CJob *job)
{
  m_refreshTime = CTimeUtils::GetFrameTime() + m_timeToRefresh;
  m_busy = false;
}

CStdString CInfoLoader::GetInfo(int info)
{
  // Refresh if need be
  if (m_refreshTime < CTimeUtils::GetFrameTime() && !m_busy)
  { // queue up the job
    m_busy = true;
    CJobManager::GetInstance().AddJob(GetJob(), this);
  }
  if (m_busy)
  {
    return BusyInfo(info);
  }
  return TranslateInfo(info);
}

CStdString CInfoLoader::BusyInfo(int info) const
{
  return g_localizeStrings.Get(503);
}

CStdString CInfoLoader::TranslateInfo(int info) const
{
  return "";
}

void CInfoLoader::Refresh()
{
  m_refreshTime = CTimeUtils::GetFrameTime();
}

