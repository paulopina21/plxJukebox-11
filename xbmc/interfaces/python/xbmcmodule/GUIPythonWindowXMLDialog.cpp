

#include "GUIPythonWindowXMLDialog.h"
#include "guilib/GUIWindowManager.h"
#include "Application.h"
#include "threads/SingleLock.h"

CGUIPythonWindowXMLDialog::CGUIPythonWindowXMLDialog(int id, CStdString strXML, CStdString strFallBackPath)
: CGUIPythonWindowXML(id,strXML,strFallBackPath)
{
  m_loadOnDemand = false;
}

CGUIPythonWindowXMLDialog::~CGUIPythonWindowXMLDialog(void)
{
}

bool CGUIPythonWindowXMLDialog::OnMessage(CGUIMessage &message)
{
  if (message.GetMessage() == GUI_MSG_WINDOW_DEINIT)
  {
    CGUIWindow *pWindow = g_windowManager.GetWindow(g_windowManager.GetActiveWindow());
    if (pWindow)
      g_windowManager.ShowOverlay(pWindow->GetOverlayState());
    return CGUIWindow::OnMessage(message);
  }
  return CGUIPythonWindowXML::OnMessage(message);
}

void CGUIPythonWindowXMLDialog::Show_Internal(bool show /* = true */)
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

void CGUIPythonWindowXMLDialog::OnDeinitWindow(int nextWindowID)
{
  g_windowManager.RemoveDialog(GetID());
  CGUIPythonWindowXML::OnDeinitWindow(nextWindowID);
}
