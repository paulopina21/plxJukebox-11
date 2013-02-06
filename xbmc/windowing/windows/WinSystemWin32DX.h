

#ifndef WIN_SYSTEM_WIN32_DX_H
#define WIN_SYSTEM_WIN32_DX_H

#ifdef HAS_DX

#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <dxdiag.h>
#include "windowing/windows/WinSystemWin32.h"
#include "rendering/dx/RenderSystemDX.h"
#include "utils/GlobalsHandling.h"


class CWinSystemWin32DX : public CWinSystemWin32, public CRenderSystemDX
{
public:
  CWinSystemWin32DX();
  ~CWinSystemWin32DX();

  virtual bool CreateNewWindow(CStdString name, bool fullScreen, RESOLUTION_INFO& res, PHANDLE_EVENT_FUNC userFunction);
  virtual bool ResizeWindow(int newWidth, int newHeight, int newLeft, int newTop);
  virtual void OnMove(int x, int y);
  virtual bool SetFullScreen(bool fullScreen, RESOLUTION_INFO& res, bool blankOtherDisplays);
  virtual bool WindowedMode() { return CRenderSystemDX::m_useWindowedDX; }

protected:
  virtual void UpdateMonitor();
  bool UseWindowedDX(bool fullScreen);
};

XBMC_GLOBAL_REF(CWinSystemWin32DX,g_Windowing);
#define g_Windowing XBMC_GLOBAL_USE(CWinSystemWin32DX)

#endif

#endif // WIN_SYSTEM_WIN32_DX_H
