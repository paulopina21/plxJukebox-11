#pragma once



#include "GUIDialogBoxBase.h"

class CGUIDialogYesNo :
      public CGUIDialogBoxBase
{
public:
  CGUIDialogYesNo(int overrideId = -1);
  virtual ~CGUIDialogYesNo(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnBack(int actionID);

  static bool ShowAndGetInput(int heading, int line0, int line1, int line2, int iNoLabel=-1, int iYesLabel=-1);
  static bool ShowAndGetInput(int heading, int line0, int line1, int line2, bool& bCanceled);
  static bool ShowAndGetInput(int heading, int line0, int line1, int line2, int iNoLabel, int iYesLabel, bool& bCanceled, unsigned int autoCloseTime = 0);
  static bool ShowAndGetInput(const CStdString& heading, const CStdString& line0, const CStdString& line1, const CStdString& line2, const CStdString& noLabel="", const CStdString& yesLabel="");
  static bool ShowAndGetInput(const CStdString& heading, const CStdString& line0, const CStdString& line1, const CStdString& line2, bool &bCanceled, const CStdString& noLabel="", const CStdString& yesLabel="");
protected:
  bool m_bCanceled;
};
