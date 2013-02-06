

#include "GUIDialogTextViewer.h"
#include "GUIUserMessages.h"

#define CONTROL_HEADING  1
#define CONTROL_TEXTAREA 5

CGUIDialogTextViewer::CGUIDialogTextViewer(void)
    : CGUIDialog(WINDOW_DIALOG_TEXT_VIEWER, "DialogTextViewer.xml")
{}

CGUIDialogTextViewer::~CGUIDialogTextViewer(void)
{}

bool CGUIDialogTextViewer::OnAction(const CAction &action)
{
  return CGUIDialog::OnAction(action);
}

bool CGUIDialogTextViewer::OnMessage(CGUIMessage& message)
{
  switch ( message.GetMessage() )
  {
  case GUI_MSG_WINDOW_INIT:
    {
      CGUIDialog::OnMessage(message);
      SetHeading();
      SetText();
      return true;
    }
    break;
  case GUI_MSG_NOTIFY_ALL:
    {
      if (message.GetParam1() == GUI_MSG_UPDATE)
      {
        SetText();
        SetHeading();
        return true;
      }
    }
    break;
  default:
    break;
  }
  return CGUIDialog::OnMessage(message);
}

void CGUIDialogTextViewer::SetText()
{
  CGUIMessage msg(GUI_MSG_LABEL_SET, GetID(), CONTROL_TEXTAREA);
  msg.SetLabel(m_strText);
  OnMessage(msg);
}

void CGUIDialogTextViewer::SetHeading()
{
  CGUIMessage msg(GUI_MSG_LABEL_SET, GetID(), CONTROL_HEADING);
  msg.SetLabel(m_strHeading);
  OnMessage(msg);
}

