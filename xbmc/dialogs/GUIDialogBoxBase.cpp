

#include "Application.h"
#include "GUIDialogBoxBase.h"
#include "guilib/GUIWindowManager.h"
#include "guilib/LocalizeStrings.h"

using namespace std;

CGUIDialogBoxBase::CGUIDialogBoxBase(int id, const CStdString &xmlFile)
    : CGUIDialog(id, xmlFile)
{
  m_bConfirmed = false;
}

CGUIDialogBoxBase::~CGUIDialogBoxBase(void)
{
}

bool CGUIDialogBoxBase::OnMessage(CGUIMessage& message)
{
  switch ( message.GetMessage() )
  {
  case GUI_MSG_WINDOW_INIT:
    {
      CGUIDialog::OnMessage(message);
      m_bConfirmed = false;
      return true;
    }
    break;
  }
  return CGUIDialog::OnMessage(message);
}

bool CGUIDialogBoxBase::IsConfirmed() const
{
  return m_bConfirmed;
}

void CGUIDialogBoxBase::SetHeading(const CVariant& heading)
{
  Initialize();
  CGUIMessage msg(GUI_MSG_LABEL_SET, GetID(), 1);
  msg.SetLabel(GetLocalized(heading));

  if(g_application.IsCurrentThread())
    OnMessage(msg);
  else
    g_windowManager.SendThreadMessage(msg, GetID());
}

void CGUIDialogBoxBase::SetLine(int iLine, const CVariant& line)
{
  Initialize();
  CGUIMessage msg(GUI_MSG_LABEL_SET, GetID(), iLine + 2);
  msg.SetLabel(GetLocalized(line));

  if(g_application.IsCurrentThread())
    OnMessage(msg);
  else
    g_windowManager.SendThreadMessage(msg, GetID());
}

void CGUIDialogBoxBase::SetChoice(int iButton, const CVariant &choice) // iButton == 0 for no, 1 for yes
{
  Initialize();
  CGUIMessage msg(GUI_MSG_LABEL_SET, GetID(), 10+iButton);
  msg.SetLabel(GetLocalized(choice));

  if(g_application.IsCurrentThread())
    OnMessage(msg);
  else
    g_windowManager.SendThreadMessage(msg, GetID());
}

void CGUIDialogBoxBase::OnInitWindow()
{
  // set focus to default
  m_lastControlID = m_defaultControl;
  CGUIDialog::OnInitWindow();
}

CStdString CGUIDialogBoxBase::GetLocalized(const CVariant &var) const
{
  if (var.isString())
    return var.asString();
  else if (var.isInteger() && var.asInteger())
    return g_localizeStrings.Get((uint32_t)var.asInteger());
  return "";
}
