

#include "RenderSystem.h"

CRenderSystemBase::CRenderSystemBase()
{
  m_bRenderCreated = false;
  m_bVSync = true;
  m_maxTextureSize = 2048;
  m_RenderVersionMajor = 0;
  m_RenderVersionMinor = 0;
  m_renderCaps = 0;
  m_renderQuirks = 0;
  m_minDXTPitch = 0;
}

CRenderSystemBase::~CRenderSystemBase()
{

}

void CRenderSystemBase::GetRenderVersion(unsigned int& major, unsigned int& minor) const
{
  major = m_RenderVersionMajor;
  minor = m_RenderVersionMinor;
}

bool CRenderSystemBase::SupportsNPOT(bool dxt) const
{
  if (dxt)
    return (m_renderCaps & RENDER_CAPS_DXT_NPOT) == RENDER_CAPS_DXT_NPOT;
  return (m_renderCaps & RENDER_CAPS_NPOT) == RENDER_CAPS_NPOT;
}

bool CRenderSystemBase::SupportsDXT() const
{
  return (m_renderCaps & RENDER_CAPS_DXT) == RENDER_CAPS_DXT;
}

bool CRenderSystemBase::SupportsBGRA() const
{
  return (m_renderCaps & RENDER_CAPS_BGRA) == RENDER_CAPS_BGRA;
}

bool CRenderSystemBase::SupportsBGRAApple() const
{
  return (m_renderCaps & RENDER_CAPS_BGRA_APPLE) == RENDER_CAPS_BGRA_APPLE;
}

