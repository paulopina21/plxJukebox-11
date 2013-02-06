

#include "GUIDialogOK.h"
#include "guilib/GUIWindowManager.h"

#define ID_BUTTON_OK   10

CGUIDialogOK::CGUIDialogOK(void)
    : CGUIDialogBoxBase(WINDOW_DIALOG_OK, "DialogOK.xml")
{
}

CGUIDialogOK::~CGUIDialogOK(void)
{}

bool CGUIDialogOK::OnMessage(CGUIMessage& message)
{
  if (message.GetMessage() == GUI_MSG_CLICKED)
  {
    int iControl = message.GetSenderId();
    if (iControl == ID_BUTTON_OK)
    {
      m_bConfirmed = true;
      Close();
      return true;
    }
  }
  return CGUIDialogBoxBase::OnMessage(message);
}

// \brief Show CGUIDialogOK dialog, then wait for user to dismiss it.
void CGUIDialogOK::ShowAndGetInput(const CVariant &heading, const CVariant &line0, const CVariant &line1, const CVariant &line2)
{
  CGUIDialogOK *dialog = (CGUIDialogOK *)g_windowManager.GetWindow(WINDOW_DIALOG_OK);
  if (!dialog) 
    return;
  dialog->SetHeading(heading);
  dialog->SetLine(0, line0);
  dialog->SetLine(1, line1);
  dialog->SetLine(2, line2);
  dialog->DoModal();
}
