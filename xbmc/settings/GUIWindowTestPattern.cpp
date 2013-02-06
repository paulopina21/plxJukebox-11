

#include "GUIWindowTestPattern.h"
#include "settings/Settings.h"
#include "guilib/GUIWindowManager.h"
#include "guilib/Key.h"

CGUIWindowTestPattern::CGUIWindowTestPattern(void)
    : CGUIWindow(WINDOW_TEST_PATTERN, "")
{
  m_needsScaling = false;
}

CGUIWindowTestPattern::~CGUIWindowTestPattern(void)
{}


bool CGUIWindowTestPattern::OnAction(const CAction &action)
{
  switch (action.GetID())
  {
  case ACTION_MOVE_UP:
  case ACTION_MOVE_LEFT:
    m_pattern = m_pattern > 0 ? m_pattern - 1 : TEST_PATTERNS_COUNT - 1;
    SetInvalid();
    return true;

  case ACTION_MOVE_DOWN:
  case ACTION_MOVE_RIGHT:
    m_pattern = (m_pattern + 1) % TEST_PATTERNS_COUNT;
    SetInvalid();
    return true;
  }
  return CGUIWindow::OnAction(action); // base class to handle basic movement etc.
}

bool CGUIWindowTestPattern::OnMessage(CGUIMessage& message)
{
  switch (message.GetMessage())
  {
  case GUI_MSG_WINDOW_INIT:
    m_pattern = 0;
    m_bounceDirectionX = 1;
    m_bounceDirectionY = 1;
    m_bounceX = 0;
    m_bounceY = 0;
    m_blinkFrame = 0;
    break;

  }
  return CGUIWindow::OnMessage(message);
}

void CGUIWindowTestPattern::Process(unsigned int currentTime, CDirtyRegionList &dirtyregions)
{
  if (m_pattern == 0 || m_pattern == 4)
    MarkDirtyRegion();
  CGUIWindow::Process(currentTime, dirtyregions);
  m_renderRegion.SetRect(0, 0, (float)g_graphicsContext.GetWidth(), (float)g_graphicsContext.GetHeight());
}

void CGUIWindowTestPattern::Render()
{
  BeginRender();

  int top = g_settings.m_ResInfo[g_graphicsContext.GetVideoResolution()].Overscan.top;
  int bottom = g_settings.m_ResInfo[g_graphicsContext.GetVideoResolution()].Overscan.bottom;
  int left = g_settings.m_ResInfo[g_graphicsContext.GetVideoResolution()].Overscan.left;
  int right = g_settings.m_ResInfo[g_graphicsContext.GetVideoResolution()].Overscan.right;

  switch (m_pattern)
  {
    case 0:
      DrawContrastBrightnessPattern(top, left, bottom, right);
      break;

    case 1:
      DrawVerticalLines(top, left, bottom, right);
      break;

    case 2:
      DrawHorizontalLines(top, left, bottom, right);
      break;

    case 3:
      DrawCheckers(top, left, bottom, right);
      break;

    case 4:
      DrawBouncingRectangle(top, left, bottom, right);
      break;
  }

  EndRender();

  CGUIWindow::Render();
}

