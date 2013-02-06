/*!
\file Surface.h
\brief
*/

#ifndef WINDOW_SYSTEM_WIN32_GL_H
#define WINDOW_SYSTEM_WIN32_GL_H

#pragma once


#include "WinSystemWin32.h"
#include "rendering/gl/RenderSystemGL.h"
#include "utils/GlobalsHandling.h"

class CWinSystemWin32GL : public CWinSystemWin32, public CRenderSystemGL
{
public:
  CWinSystemWin32GL();
  virtual ~CWinSystemWin32GL();

  virtual bool InitRenderSystem();
  virtual bool ResizeWindow(int newWidth, int newHeight, int newLeft, int newTop);
  virtual bool SetFullScreen(bool fullScreen, RESOLUTION_INFO& res, bool blankOtherDisplays);

protected:
  virtual void SetVSyncImpl(bool enable);
  virtual bool PresentRenderImpl(const CDirtyRegionList& dirty);
  HGLRC m_hglrc;
  BOOL (APIENTRY *m_wglSwapIntervalEXT)( int );
};

#ifdef HAS_GL

XBMC_GLOBAL_REF(CWinSystemWin32GL,g_Windowing);
#define g_Windowing XBMC_GLOBAL_USE(CWinSystemWin32GL)

#endif

#endif // WINDOW_SYSTEM_H

