#pragma once



#include "guilib/GUIWindow.h"

class CGUIWindowStartup :
      public CGUIWindow
{
public:
  CGUIWindowStartup(void);
  virtual ~CGUIWindowStartup(void);
  virtual bool OnAction(const CAction &action);
};
