


#include "WinSystemWin32DX.h"
#include "settings/GUISettings.h"
#include "guilib/gui3d.h"

#ifdef HAS_DX

CWinSystemWin32DX::CWinSystemWin32DX()
: CRenderSystemDX()
{

}

CWinSystemWin32DX::~CWinSystemWin32DX()
{

}

bool CWinSystemWin32DX::UseWindowedDX(bool fullScreen)
{
  return (g_guiSettings.GetBool("videoscreen.fakefullscreen") || !fullScreen);
}

bool CWinSystemWin32DX::CreateNewWindow(CStdString name, bool fullScreen, RESOLUTION_INFO& res, PHANDLE_EVENT_FUNC userFunction)
{
  CWinSystemWin32::CreateNewWindow(name, fullScreen, res, userFunction);

  if(m_hWnd == NULL)
    return false;

  SetFocusWnd(m_hWnd);
  SetDeviceWnd(m_hWnd);
  CRenderSystemDX::m_interlaced = ((res.dwFlags & D3DPRESENTFLAG_INTERLACED) != 0);
  CRenderSystemDX::m_useWindowedDX = UseWindowedDX(fullScreen);
  SetRenderParams(m_nWidth, m_nHeight, fullScreen, res.fRefreshRate);
  SetMonitor(GetMonitor(res.iScreen).hMonitor);

  return true;
}

void CWinSystemWin32DX::UpdateMonitor()
{
  SetMonitor(GetMonitor(m_nScreen).hMonitor);
}

bool CWinSystemWin32DX::ResizeWindow(int newWidth, int newHeight, int newLeft, int newTop)
{
  CWinSystemWin32::ResizeWindow(newWidth, newHeight, newLeft, newTop);
  CRenderSystemDX::ResetRenderSystem(newWidth, newHeight, false, 0);

  return true;
}

void CWinSystemWin32DX::OnMove(int x, int y)
{
  CRenderSystemDX::OnMove();
}

bool CWinSystemWin32DX::SetFullScreen(bool fullScreen, RESOLUTION_INFO& res, bool blankOtherDisplays)
{
  // When going DX fullscreen -> windowed, we must reset the D3D device first to
  // get it out of fullscreen mode because it restores a former resolution.
  // We then change to the mode we want.
  // In other cases, set the window/mode then reset the D3D device.

  bool FS2Windowed = !m_useWindowedDX && UseWindowedDX(fullScreen);

  SetMonitor(GetMonitor(res.iScreen).hMonitor);
  CRenderSystemDX::m_interlaced = ((res.dwFlags & D3DPRESENTFLAG_INTERLACED) != 0);
  CRenderSystemDX::m_useWindowedDX = UseWindowedDX(fullScreen);

  if (FS2Windowed)
    CRenderSystemDX::ResetRenderSystem(res.iWidth, res.iHeight, fullScreen, res.fRefreshRate);

  CWinSystemWin32::SetFullScreen(fullScreen, res, blankOtherDisplays);
  CRenderSystemDX::ResetRenderSystem(res.iWidth, res.iHeight, fullScreen, res.fRefreshRate);

  return true;
}

#endif
