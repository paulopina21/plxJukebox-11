#pragma once



#include "StdString.h"
#include "Job.h"

class CInfoLoader : public IJobCallback
{
public:
  CInfoLoader(unsigned int timeToRefresh = 5 * 60 * 1000);
  virtual ~CInfoLoader();

  CStdString GetInfo(int info);
  void Refresh();

  virtual void OnJobComplete(unsigned int jobID, bool success, CJob *job);
protected:
  virtual CJob *GetJob() const=0;
  virtual CStdString TranslateInfo(int info) const;
  virtual CStdString BusyInfo(int info) const;
private:
  unsigned int m_refreshTime;
  unsigned int m_timeToRefresh;
  bool m_busy;
};
