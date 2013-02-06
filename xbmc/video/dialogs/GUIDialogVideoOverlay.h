#pragma once



#include "guilib/GUIDialog.h"

class CGUIDialogVideoOverlay: public CGUIDialog
{
public:
  CGUIDialogVideoOverlay(void);
  virtual ~CGUIDialogVideoOverlay(void);
  virtual void FrameMove();
protected:
  virtual EVENT_RESULT OnMouseEvent(const CPoint &point, const CMouseEvent &event);
  virtual void SetDefaults();
};
