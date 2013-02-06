#pragma once



#include "guilib/GUIDialog.h"

class CGUIDialogMusicOSD :
      public CGUIDialog
{
public:
  CGUIDialogMusicOSD(void);
  virtual ~CGUIDialogMusicOSD(void);
  virtual bool OnMessage(CGUIMessage &message);
  virtual void FrameMove();
};
