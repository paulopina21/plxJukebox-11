#ifndef WINDOW_SYSTEM_EGLGLES_H
#define WINDOW_SYSTEM_EGLGLES_H

#pragma once



#include "rendering/gles/RenderSystemGLES.h"
#include "utils/GlobalsHandling.h"
#include "windowing/WinSystem.h"

class CWinBindingEGL;

typedef struct fbdev_window fbdev_window;

class CWinSystemGLES : public CWinSystemBase, public CRenderSystemGLES
{
public:
  CWinSystemGLES();
  virtual ~CWinSystemGLES();

  virtual bool  InitWindowSystem();
  virtual bool  DestroyWindowSystem();
  virtual bool  CreateNewWindow(const CStdString& name, bool fullScreen, RESOLUTION_INFO& res, PHANDLE_EVENT_FUNC userFunction);
  virtual bool  DestroyWindow();
  virtual bool  ResizeWindow(int newWidth, int newHeight, int newLeft, int newTop);
  virtual bool  SetFullScreen(bool fullScreen, RESOLUTION_INFO& res, bool blankOtherDisplays);
  virtual void  UpdateResolutions();
  virtual bool  IsExtSupported(const char* extension);

  virtual void  ShowOSMouse(bool show);

  virtual void  NotifyAppActiveChange(bool bActivated);

  virtual bool  Minimize();
  virtual bool  Restore() ;
  virtual bool  Hide();
  virtual bool  Show(bool raise = true);

protected:
  virtual bool  PresentRenderImpl(const CDirtyRegionList &dirty);
  virtual void  SetVSyncImpl(bool enable);
  void                  *m_display;
  fbdev_window          *m_window;
  CWinBindingEGL        *m_eglBinding;
  int                   m_fb_width;
  int                   m_fb_height;
  int                   m_fb_bpp;
};

XBMC_GLOBAL_REF(CWinSystemGLES,g_Windowing);
#define g_Windowing XBMC_GLOBAL_USE(CWinSystemGLES)

#endif // WINDOW_SYSTEM_EGLGLES_H
