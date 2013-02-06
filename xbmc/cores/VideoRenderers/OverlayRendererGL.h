

#pragma once
#include "OverlayRenderer.h"

#ifdef HAS_GL
#include <GL/glew.h>
#endif

class CDVDOverlay;
class CDVDOverlayImage;
class CDVDOverlaySpu;
class CDVDOverlaySSA;

#if defined(HAS_GL) || HAS_GLES == 2

namespace OVERLAY {

  class COverlayTextureGL
      : public COverlayMainThread
  {
  public:
     COverlayTextureGL(CDVDOverlayImage* o);
     COverlayTextureGL(CDVDOverlaySpu* o);
    virtual ~COverlayTextureGL();

    void Render(SRenderState& state);

    GLuint m_texture;
    float  m_u;
    float  m_v;
  };

  class COverlayGlyphGL
     : public COverlayMainThread
  {
  public:
   COverlayGlyphGL(CDVDOverlaySSA* o, double pts);
   virtual ~COverlayGlyphGL();

   void Render(SRenderState& state);

    struct VERTEX
    {
       GLfloat u, v;
       GLubyte r, g, b, a;
       GLfloat x, y, z;
    };

   VERTEX* m_vertex;
   int     m_count;

   GLuint m_texture;
   float  m_u;
   float  m_v;
  };

}

#endif

