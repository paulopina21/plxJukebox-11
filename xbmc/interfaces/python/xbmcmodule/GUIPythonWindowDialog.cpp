

#include "GUIPythonWindowDialog.h"
#include "guilib/GUIWindowManager.h"
#include "Application.h"
#include "threads/SingleLock.h"

CGUIPythonWindowDialog::CGUIPythonWindowDialog(int id)
:CGUIPythonWindow(id)
{
  m_loadOnDemand = false;
}

CGUIPythonWindowDialog::~CGUIPythonWindowDialog(void)
{
}

bool CGUIPythonWindowDialog::OnMessage(CGUIMessage& message)
{
  switch(message.GetMessage())
  {
    case GUI_MSG_WINDOW_INIT:
    {
      CGUIWindow::OnMessage(message);
      return true;
    }
    break;

    case GUI_MSG_CLICKED:
    {
      return CGUIPythonWindow::OnMessage(message);
    }
    break;
  }

  // we do not message CGUIPythonWindow here..
  return CGUIWindow::OnMessage(message);
}

void CGUIPythonWindowDialog::Show_Internal(bool show /* = true */)
{
  if (show)
  {
    g_windowManager.RouteToWindow(this);

    // active this dialog...
    CGUIMessage msg(GUI_MSG_WINDOW_INIT,0,0);
    OnMessage(msg);
    m_active = true;
  }
  else // hide
    Close();
}

void CGUIPythonWindowDialog::OnDeinitWindow(int nextWindowID)
{
  g_windowManager.RemoveDialog(GetID());
  CGUIPythonWindow::OnDeinitWindow(nextWindowID);
}
