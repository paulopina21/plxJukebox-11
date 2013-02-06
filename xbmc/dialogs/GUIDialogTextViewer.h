#pragma once



#include "guilib/GUIDialog.h"

class CGUIDialogTextViewer :
      public CGUIDialog
{
public:
  CGUIDialogTextViewer(void);
  virtual ~CGUIDialogTextViewer(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
  void SetText(const CStdString& strText) { m_strText = strText; }
  void SetHeading(const CStdString& strHeading) { m_strHeading = strHeading; }
protected:
  CStdString m_strText;
  CStdString m_strHeading;

  void SetText();
  void SetHeading();
};

