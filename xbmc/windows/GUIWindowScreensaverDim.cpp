

#include "GUIWindowScreensaverDim.h"
#include "guilib/GraphicContext.h"
#include "guilib/GUITexture.h"
#include "Application.h"
#include <climits>

CGUIWindowScreensaverDim::CGUIWindowScreensaverDim(void)
    : CGUIDialog(97, "")
{
  m_needsScaling = false;
  m_dimLevel = 100.0f;
  m_animations.push_back(CAnimation::CreateFader(0, 100, 0, 1000, ANIM_TYPE_WINDOW_OPEN));
  m_animations.push_back(CAnimation::CreateFader(100, 0, 0, 1000, ANIM_TYPE_WINDOW_CLOSE));
  m_renderOrder = INT_MAX;
}

CGUIWindowScreensaverDim::~CGUIWindowScreensaverDim(void)
{
}

void CGUIWindowScreensaverDim::UpdateVisibility()
{
  float level = g_application.GetDimScreenSaverLevel();
  if (level)
  {
    m_dimLevel = level;
    Show();
  }
  else
    Close();
}

void CGUIWindowScreensaverDim::Process(unsigned int currentTime, CDirtyRegionList &dirtyregions)
{
  CGUIDialog::Process(currentTime, dirtyregions);
  m_renderRegion.SetRect(0, 0, (float)g_graphicsContext.GetWidth(), (float)g_graphicsContext.GetHeight());
}

void CGUIWindowScreensaverDim::Render()
{
  // draw a translucent black quad - fading is handled by the window animation
  color_t color = ((color_t)(m_dimLevel * 2.55f) & 0xff) << 24;
  color = g_graphicsContext.MergeAlpha(color);
  CRect rect(0, 0, (float)g_graphicsContext.GetWidth(), (float)g_graphicsContext.GetHeight());
  CGUITexture::DrawQuad(rect, color);
  CGUIDialog::Render();
}
