
#pragma once

#include "DllAvCodec.h"
#include "DVDVideoCodecFFmpeg.h"
#include <libavcodec/vaapi.h>
#include <va/va.h>
#include <va/va_x11.h>
#include <va/va_glx.h>
#include <list>
#include <boost/shared_ptr.hpp>


namespace VAAPI {

typedef boost::shared_ptr<VASurfaceID const> VASurfacePtr;

struct CDisplay
  : CCriticalSection
{
  CDisplay(VADisplay display, bool deinterlace)
    : m_display(display)
    , m_lost(false)
    , m_deinterlace(deinterlace)
  {}
 ~CDisplay();

  VADisplay get() { return m_display; }
  bool      lost()          { return m_lost; }
  void      lost(bool lost) { m_lost = lost; }
  bool      support_deinterlace() { return m_deinterlace; };
private:
  VADisplay m_display;
  bool      m_lost;
  bool      m_deinterlace;
};

typedef boost::shared_ptr<CDisplay> CDisplayPtr;

struct CSurface
{
  CSurface(VASurfaceID id, CDisplayPtr& display)
   : m_id(id)
   , m_display(display)
  {}

 ~CSurface();

  VASurfaceID m_id;
  CDisplayPtr m_display;
};

typedef boost::shared_ptr<CSurface> CSurfacePtr;

struct CSurfaceGL
{
  CSurfaceGL(void* id, CDisplayPtr& display)
    : m_id(id)
    , m_display(display)
  {}
 ~CSurfaceGL();
 
  void*       m_id;
  CDisplayPtr m_display;
};

typedef boost::shared_ptr<CSurfaceGL> CSurfaceGLPtr;

// silly type to avoid includes
struct CHolder
{
  CDisplayPtr   display;
  CSurfacePtr   surface;
  CSurfaceGLPtr surfglx;

  CHolder()
  {}
};

class CDecoder
  : public CDVDVideoCodecFFmpeg::IHardwareDecoder
{
  bool EnsureContext(AVCodecContext *avctx);
  bool EnsureSurfaces(AVCodecContext *avctx, unsigned n_surfaces_count);
public:
  CDecoder();
 ~CDecoder();
  virtual bool Open      (AVCodecContext* avctx, const enum PixelFormat, unsigned int surfaces = 0);
  virtual int  Decode    (AVCodecContext* avctx, AVFrame* frame);
  virtual bool GetPicture(AVCodecContext* avctx, AVFrame* frame, DVDVideoPicture* picture);
  virtual int  Check     (AVCodecContext* avctx);
  virtual void Close();
  virtual const std::string Name() { return "vaapi"; }
  virtual CCriticalSection* Section() { if(m_display) return m_display.get(); else return NULL; }

  int   GetBuffer(AVCodecContext *avctx, AVFrame *pic);
  void  RelBuffer(AVCodecContext *avctx, AVFrame *pic);

  VADisplay    GetDisplay() { return m_display->get(); }
protected:
  
  static const unsigned  m_surfaces_max = 32;
  unsigned               m_surfaces_count;
  VASurfaceID            m_surfaces[m_surfaces_max];

  int                    m_refs;
  std::list<CSurfacePtr> m_surfaces_used;
  std::list<CSurfacePtr> m_surfaces_free;

  CDisplayPtr    m_display;
  VAConfigID     m_config;
  VAContextID    m_context;

  vaapi_context *m_hwaccel;

  CHolder        m_holder; // silly struct to pass data to renderer
};

}
