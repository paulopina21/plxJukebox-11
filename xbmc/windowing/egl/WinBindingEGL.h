

#ifndef WINDOW_BINDING_EGL_H
#define WINDOW_BINDING_EGL_H

#include "utils/StringUtils.h"

#include <EGL/egl.h>
#ifndef TARGET_WINDOWS
#include <EGL/eglext.h>
#endif

class CWinBindingEGL
{
public:
  CWinBindingEGL();
  ~CWinBindingEGL();

  bool  CreateWindow(EGLNativeDisplayType nativeDisplay, EGLNativeWindowType nativeWindow);
  bool  DestroyWindow();
  bool  ReleaseSurface();
  void  SwapBuffers();
  bool  SetVSync(bool enable);
  bool  IsExtSupported(const char* extension);

  EGLNativeWindowType   GetNativeWindow();
  EGLNativeDisplayType  GetNativeDisplay();
  EGLDisplay            GetDisplay();
  EGLSurface            GetSurface();
  EGLContext            GetContext();

protected:
  EGLNativeWindowType   m_nativeWindow;
  EGLNativeDisplayType  m_nativeDisplay;
  EGLDisplay            m_display;
  EGLSurface            m_surface;
  EGLConfig             m_config;
  EGLContext            m_context;
  CStdString            m_eglext;
};

#endif // WINDOW_BINDING_EGL_H

