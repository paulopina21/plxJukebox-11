

#include "GUIDialogMusicOSD.h"
#include "Application.h"
#include "guilib/GUIWindowManager.h"
#include "input/MouseStat.h"
#include "GUIUserMessages.h"
#include "settings/Settings.h"
#include "settings/GUISettings.h"
#include "addons/GUIWindowAddonBrowser.h"

#define CONTROL_VIS_BUTTON       500
#define CONTROL_LOCK_BUTTON      501

CGUIDialogMusicOSD::CGUIDialogMusicOSD(void)
    : CGUIDialog(WINDOW_DIALOG_MUSIC_OSD, "MusicOSD.xml")
{
}

CGUIDialogMusicOSD::~CGUIDialogMusicOSD(void)
{
}

bool CGUIDialogMusicOSD::OnMessage(CGUIMessage &message)
{
  switch (message.GetMessage())
  {
  case GUI_MSG_CLICKED:
    {
      unsigned int iControl = message.GetSenderId();
      if (iControl == CONTROL_VIS_BUTTON)
      {
        CStdString addonID;
        if (CGUIWindowAddonBrowser::SelectAddonID(ADDON::ADDON_VIZ, addonID, true) == 1)
        {
          g_guiSettings.SetString("musicplayer.visualisation", addonID);
          g_settings.Save();
          g_windowManager.SendMessage(GUI_MSG_VISUALISATION_RELOAD, 0, 0);
        }
      }
      else if (iControl == CONTROL_LOCK_BUTTON)
      {
        CGUIMessage msg(GUI_MSG_VISUALISATION_ACTION, 0, 0, ACTION_VIS_PRESET_LOCK);
        g_windowManager.SendMessage(msg);
      }
      return true;
    }
    break;
  }
  return CGUIDialog::OnMessage(message);
}

void CGUIDialogMusicOSD::FrameMove()
{
  if (m_autoClosing)
  {
    // check for movement of mouse or a submenu open
    if (g_Mouse.IsActive() || g_windowManager.IsWindowActive(WINDOW_DIALOG_VIS_SETTINGS)
                           || g_windowManager.IsWindowActive(WINDOW_DIALOG_VIS_PRESET_LIST))
      SetAutoClose(100); // enough for 10fps
  }
  CGUIDialog::FrameMove();
}
