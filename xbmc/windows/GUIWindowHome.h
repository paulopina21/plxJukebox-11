#pragma once



#include "guilib/GUIWindow.h"
#include "interfaces/IAnnouncer.h"
#include "utils/Job.h"

class CGUIWindowHome :
      public CGUIWindow,
      public ANNOUNCEMENT::IAnnouncer,
      public IJobCallback
{
public:
  CGUIWindowHome(void);
  virtual ~CGUIWindowHome(void);
  virtual void OnInitWindow();
  virtual void Announce(ANNOUNCEMENT::EAnnouncementFlag flag, const char *sender, const char *message, const CVariant &data);

  virtual bool OnMessage(CGUIMessage& message);

  virtual void OnJobComplete(unsigned int jobID, bool success, CJob *job);
private:
  int m_updateRA; // flag for which recently added items needs to be queried
  void AddRecentlyAddedJobs(int flag);

  bool m_recentlyAddedRunning;
  int m_cumulativeUpdateFlag;
};
