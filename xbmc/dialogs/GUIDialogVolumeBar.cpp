

#include "GUIDialogVolumeBar.h"
#include "utils/TimeUtils.h"

#define VOLUME_BAR_DISPLAY_TIME 1000L

CGUIDialogVolumeBar::CGUIDialogVolumeBar(void)
    : CGUIDialog(WINDOW_DIALOG_VOLUME_BAR, "DialogVolumeBar.xml")
{
  m_loadOnDemand = false;
  SetAutoClose(VOLUME_BAR_DISPLAY_TIME);
}

CGUIDialogVolumeBar::~CGUIDialogVolumeBar(void)
{}

bool CGUIDialogVolumeBar::OnAction(const CAction &action)
{
  if (action.GetID() == ACTION_VOLUME_UP || action.GetID() == ACTION_VOLUME_DOWN)
  { // reset the timer, as we've changed the volume level
    SetAutoClose(VOLUME_BAR_DISPLAY_TIME);
    return true;
  }
  return CGUIDialog::OnAction(action);
}

bool CGUIDialogVolumeBar::OnMessage(CGUIMessage& message)
{
  switch ( message.GetMessage() )
  {
  case GUI_MSG_WINDOW_INIT:
  case GUI_MSG_WINDOW_DEINIT:
    return CGUIDialog::OnMessage(message);
  }
  return false; // don't process anything other than what we need!
}
