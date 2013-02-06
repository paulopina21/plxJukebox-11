#pragma once



#include "guilib/GUIDialog.h"

class CGUIWindowScreensaverDim :
      public CGUIDialog
{
public:
  CGUIWindowScreensaverDim();
  virtual ~CGUIWindowScreensaverDim();
  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
protected:
  virtual void UpdateVisibility();
private:
  float m_dimLevel;
};
