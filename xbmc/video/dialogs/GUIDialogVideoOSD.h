#pragma once



#include "guilib/GUIDialog.h"

class CGUIDialogVideoOSD : public CGUIDialog
{
public:

  CGUIDialogVideoOSD(void);
  virtual ~CGUIDialogVideoOSD(void);

  virtual void FrameMove();
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
protected:
  virtual EVENT_RESULT OnMouseEvent(const CPoint &point, const CMouseEvent &event);
};
