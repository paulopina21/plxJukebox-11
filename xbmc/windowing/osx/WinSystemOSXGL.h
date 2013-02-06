#ifndef WINDOW_SYSTEM_OSX_GL_H
#define WINDOW_SYSTEM_OSX_GL_H

#pragma once


#if !defined(__arm__)
#include "WinSystemOSX.h"
#include "rendering/gl/RenderSystemGL.h"
#include "utils/GlobalsHandling.h"

class CWinSystemOSXGL : public CWinSystemOSX, public CRenderSystemGL
{
public:
  CWinSystemOSXGL();
  virtual ~CWinSystemOSXGL();
  virtual bool ResizeWindow(int newWidth, int newHeight, int newLeft, int newTop);
  virtual bool SetFullScreen(bool fullScreen, RESOLUTION_INFO& res, bool blankOtherDisplays);

protected:
  virtual bool PresentRenderImpl(const CDirtyRegionList &dirty);
  virtual void SetVSyncImpl(bool enable);  
};

XBMC_GLOBAL_REF(CWinSystemOSXGL,g_Windowing);
#define g_Windowing XBMC_GLOBAL_USE(CWinSystemOSXGL)

#endif
#endif // WINDOW_SYSTEM_H
