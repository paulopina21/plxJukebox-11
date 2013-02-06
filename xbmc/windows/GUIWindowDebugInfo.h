#pragma once



#include "guilib/GUIDialog.h"
#ifdef _LINUX
#include "linux/LinuxResourceCounter.h"
#endif

class CGUITextLayout;

class CGUIWindowDebugInfo :
      public CGUIDialog
{
public:
  CGUIWindowDebugInfo();
  virtual ~CGUIWindowDebugInfo();
  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual bool OnMessage(CGUIMessage &message);
protected:
  virtual void UpdateVisibility();
private:
  CGUITextLayout *m_layout;
#ifdef _LINUX
  CLinuxResourceCounter m_resourceCounter;
#endif
};
