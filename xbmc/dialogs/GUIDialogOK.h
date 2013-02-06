#pragma once



#include "GUIDialogBoxBase.h"

class CGUIDialogOK :
      public CGUIDialogBoxBase
{
public:
  CGUIDialogOK(void);
  virtual ~CGUIDialogOK(void);
  virtual bool OnMessage(CGUIMessage& message);
  static void ShowAndGetInput(const CVariant &heading, const CVariant &line0, const CVariant &line1, const CVariant &line2);
};
