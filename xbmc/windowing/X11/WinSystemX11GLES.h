#ifndef WINDOW_SYSTEM_EGL_H
#define WINDOW_SYSTEM_EGL_H

#pragma once


#include "windowing/WinSystem.h"
#include <EGL/egl.h>
#include <X11/Xlib.h>
#include "rendering/gles/RenderSystemGLES.h"
#include "utils/GlobalsHandling.h"

class CWinSystemX11GLES : public CWinSystemBase, public CRenderSystemGLES
{
public:
  CWinSystemX11GLES();
  virtual ~CWinSystemX11GLES();

  virtual bool InitWindowSystem();
  virtual bool DestroyWindowSystem();
  virtual bool CreateNewWindow(const CStdString& name, bool fullScreen, RESOLUTION_INFO& res, PHANDLE_EVENT_FUNC userFunction);
  virtual bool DestroyWindow();
  virtual bool ResizeWindow(int newWidth, int newHeight, int newLeft, int newTop);
  virtual bool SetFullScreen(bool fullScreen, RESOLUTION_INFO& res, bool blankOtherDisplays);
  virtual void UpdateResolutions();

  virtual void ShowOSMouse(bool show);

  virtual void NotifyAppActiveChange(bool bActivated);

  virtual bool Minimize();
  virtual bool Restore() ;
  virtual bool Hide();
  virtual bool Show(bool raise = true);

  virtual bool IsExtSupported(const char* extension);

  virtual bool makeOMXCurrent();

  EGLContext GetEGLContext() const;
  EGLDisplay GetEGLDisplay() const;
protected:
  bool RefreshEGLContext();

  SDL_Surface* m_SDLSurface;
  EGLDisplay   m_eglDisplay;
  EGLContext   m_eglContext;
  EGLContext   m_eglOMXContext;
  EGLSurface   m_eglSurface;
  Window       m_eglWindow;
  Window       m_wmWindow;
  Display*     m_dpy;

  bool         m_bWasFullScreenBeforeMinimize;

  virtual bool PresentRenderImpl(const CDirtyRegionList &dirty);
  virtual void SetVSyncImpl(bool enable);
  
  CStdString m_eglext;

  int m_iVSyncErrors;
};

XBMC_GLOBAL_REF(CWinSystemX11GLES,g_Windowing);
#define g_Windowing XBMC_GLOBAL_USE(CWinSystemX11GLES)

#endif // WINDOW_SYSTEM_H
