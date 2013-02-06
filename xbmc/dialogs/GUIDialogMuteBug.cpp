

#include "GUIDialogMuteBug.h"
#include "GUIUserMessages.h"
#include "settings/Settings.h"

// the MuteBug is a true modeless dialog

CGUIDialogMuteBug::CGUIDialogMuteBug(void)
    : CGUIDialog(WINDOW_DIALOG_MUTE_BUG, "DialogMuteBug.xml")
{
  m_loadOnDemand = false;
}

CGUIDialogMuteBug::~CGUIDialogMuteBug(void)
{}

void CGUIDialogMuteBug::UpdateVisibility()
{
  if (g_settings.m_bMute || g_settings.m_nVolumeLevel == VOLUME_MINIMUM)
    Show();
  else
    Close();
}
