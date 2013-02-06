

#include "GUIDialogVideoOverlay.h"
#include "GUIInfoManager.h"
#include "guilib/GUIWindowManager.h"

#define CONTROL_PLAYTIME     2
#define CONTROL_PLAY_LOGO    3
#define CONTROL_PAUSE_LOGO   4
#define CONTROL_INFO         5
#define CONTROL_BIG_PLAYTIME 6
#define CONTROL_FF_LOGO      7
#define CONTROL_RW_LOGO      8


CGUIDialogVideoOverlay::CGUIDialogVideoOverlay()
    : CGUIDialog(WINDOW_DIALOG_VIDEO_OVERLAY, "VideoOverlay.xml")
{
  m_renderOrder = 0;
}

CGUIDialogVideoOverlay::~CGUIDialogVideoOverlay()
{}

void CGUIDialogVideoOverlay::FrameMove()
{
  if (g_windowManager.GetActiveWindow() == WINDOW_FULLSCREEN_VIDEO)
  { // close immediately
    Close(true);
    return;
  }
  CGUIDialog::FrameMove();
}

EVENT_RESULT CGUIDialogVideoOverlay::OnMouseEvent(const CPoint &point, const CMouseEvent &event)
{
  return EVENT_RESULT_UNHANDLED;
}

void CGUIDialogVideoOverlay::SetDefaults()
{
  CGUIDialog::SetDefaults();
  m_renderOrder = 0;
  SetVisibleCondition("skin.hasvideooverlay");
}

