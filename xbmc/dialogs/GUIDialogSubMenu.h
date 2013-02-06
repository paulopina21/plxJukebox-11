#pragma once



#include "guilib/GUIDialog.h"

class CGUIDialogSubMenu :
      public CGUIDialog
{
public:
  CGUIDialogSubMenu(int id = WINDOW_DIALOG_SUB_MENU, const CStdString &xmlFile = "DialogSubMenu.xml");
  virtual ~CGUIDialogSubMenu(void);
  virtual bool OnMessage(CGUIMessage &message);
};
