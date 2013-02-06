

#include "GUIDialogBusy.h"
#include "guilib/GUIWindowManager.h"

CGUIDialogBusy::CGUIDialogBusy(void)
  : CGUIDialog(WINDOW_DIALOG_BUSY, "DialogBusy.xml"), m_bLastVisible(false)
{
  m_loadOnDemand = false;
  m_bModal = true;
}

CGUIDialogBusy::~CGUIDialogBusy(void)
{
}

void CGUIDialogBusy::Show_Internal()
{
  m_bCanceled = false;
  m_active = true;
  m_bModal = true;
  m_bLastVisible = true;
  m_closing = false;
  g_windowManager.RouteToWindow(this);

  // active this window...
  CGUIMessage msg(GUI_MSG_WINDOW_INIT, 0, 0);
  OnMessage(msg);
}

void CGUIDialogBusy::DoProcess(unsigned int currentTime, CDirtyRegionList &dirtyregions)
{
  bool visible = g_windowManager.GetTopMostModalDialogID() == WINDOW_DIALOG_BUSY;
  if(!visible && m_bLastVisible)
    dirtyregions.push_back(m_renderRegion);
  m_bLastVisible = visible;
  CGUIDialog::DoProcess(currentTime, dirtyregions);
}

void CGUIDialogBusy::Render()
{
  if(!m_bLastVisible)
    return;
  CGUIDialog::Render();
}

bool CGUIDialogBusy::OnBack(int actionID)
{
  m_bCanceled = true;
  return true;
}
