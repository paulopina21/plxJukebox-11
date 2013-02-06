

#pragma once
#include "OverlayRenderer.h"
#include "OverlayRendererUtil.h"
#include "rendering/dx/RenderSystemDX.h"
#include "guilib/D3DResource.h"

#ifdef HAS_DX

class CDVDOverlay;
class CDVDOverlayImage;
class CDVDOverlaySpu;
class CDVDOverlaySSA;

namespace OVERLAY {

  class COverlayQuadsDX
    : public COverlayMainThread
  {
  public:
    COverlayQuadsDX(CDVDOverlaySSA* o, double pts);
    virtual ~COverlayQuadsDX();

    void Render(SRenderState& state);

    struct VERTEX {
        FLOAT x, y, z;
        DWORD c;
        FLOAT u, v;
    };

    int                          m_count;
    DWORD                        m_fvf;
    CD3DTexture                  m_texture;
    CD3DVertexBuffer             m_vertex;
  };

  class COverlayImageDX
    : public COverlayMainThread
  {
  public:
    COverlayImageDX(CDVDOverlayImage* o);
    COverlayImageDX(CDVDOverlaySpu*   o);
    virtual ~COverlayImageDX();

    void Load(uint32_t* rgba, int width, int height, int stride);
    void Render(SRenderState& state);

    struct VERTEX {
        FLOAT x, y, z;
        FLOAT u, v;
    };

    DWORD                        m_fvf;
    CD3DTexture                  m_texture;
    CD3DVertexBuffer             m_vertex;
  };

}


#endif