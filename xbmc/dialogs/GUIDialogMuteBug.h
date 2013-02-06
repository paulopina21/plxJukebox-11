#pragma once



#include "guilib/GUIDialog.h"

class CGUIDialogMuteBug : public CGUIDialog
{
public:
  CGUIDialogMuteBug(void);
  virtual ~CGUIDialogMuteBug(void);
protected:
  virtual void UpdateVisibility();
};
