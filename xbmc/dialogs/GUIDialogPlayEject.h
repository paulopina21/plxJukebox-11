#pragma once


#include "FileItem.h"
#include "GUIDialogYesNo.h"
#include "utils/Variant.h"

class CGUIDialogPlayEject : public CGUIDialogYesNo
{
public:
  CGUIDialogPlayEject();
  virtual ~CGUIDialogPlayEject();
  virtual bool OnMessage(CGUIMessage& message);
  virtual void FrameMove();

  static bool ShowAndGetInput(const CFileItem & item, unsigned int uiAutoCloseTime = 0);

protected:
  virtual void OnInitWindow();
};
