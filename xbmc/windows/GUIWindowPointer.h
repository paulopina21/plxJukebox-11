#pragma once



#include "guilib/GUIDialog.h"

class CGUIWindowPointer :
      public CGUIDialog
{
public:
  CGUIWindowPointer(void);
  virtual ~CGUIWindowPointer(void);
  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
protected:
  void SetPointer(int pointer);
  virtual void OnWindowLoaded();
  virtual void UpdateVisibility();
private:
  int m_pointer;
  bool m_active;
};
