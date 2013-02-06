#pragma once



#include "guilib/GUIDialog.h"

class CGUIDialogVolumeBar : public CGUIDialog
{
public:
  CGUIDialogVolumeBar(void);
  virtual ~CGUIDialogVolumeBar(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
};
