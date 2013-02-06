#pragma once



#include "guilib/GUIDialog.h"

class CGUIDialogMusicOverlay: public CGUIDialog
{
public:
  CGUIDialogMusicOverlay(void);
  virtual ~CGUIDialogMusicOverlay(void);
  virtual bool OnMessage(CGUIMessage& message);
protected:
  virtual EVENT_RESULT OnMouseEvent(const CPoint &point, const CMouseEvent &event);
  virtual void SetDefaults();
};
