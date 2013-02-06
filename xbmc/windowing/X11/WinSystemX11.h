#ifndef WINDOW_SYSTEM_X11_H
#define WINDOW_SYSTEM_X11_H

#pragma once


#include "windowing/WinSystem.h"
#include "utils/Stopwatch.h"
#include <GL/glx.h>
#include "threads/CriticalSection.h"

class IDispResource;

class CWinSystemX11 : public CWinSystemBase
{
public:
  CWinSystemX11();
  virtual ~CWinSystemX11();

  // CWinSystemBase
  virtual bool InitWindowSystem();
  virtual bool DestroyWindowSystem();
  virtual bool CreateNewWindow(const CStdString& name, bool fullScreen, RESOLUTION_INFO& res, PHANDLE_EVENT_FUNC userFunction);
  virtual bool DestroyWindow();
  virtual bool ResizeWindow(int newWidth, int newHeight, int newLeft, int newTop);
  virtual bool SetFullScreen(bool fullScreen, RESOLUTION_INFO& res, bool blankOtherDisplays);
  virtual void UpdateResolutions();
  virtual int  GetNumScreens() { return 1; }
  virtual void ShowOSMouse(bool show);
  virtual void ResetOSScreensaver();

  virtual void NotifyAppActiveChange(bool bActivated);

  virtual bool Minimize();
  virtual bool Restore() ;
  virtual bool Hide();
  virtual bool Show(bool raise = true);
  virtual void Register(IDispResource *resource);
  virtual void Unregister(IDispResource *resource);

  // Local to WinSystemX11 only
  Display*  GetDisplay() { return m_dpy; }
  GLXWindow GetWindow() { return m_glWindow; }

protected:
  bool RefreshGlxContext();
  void CheckDisplayEvents();
  void OnLostDevice();

  SDL_Surface* m_SDLSurface;
  GLXContext   m_glContext;
  GLXWindow    m_glWindow;
  Window       m_wmWindow;
  Display*     m_dpy;
  bool         m_bWasFullScreenBeforeMinimize;
  int          m_RREventBase;
  CCriticalSection             m_resourceSection;
  std::vector<IDispResource*>  m_resources;
  uint64_t                     m_dpyLostTime;

private:
  bool IsSuitableVisual(XVisualInfo *vInfo);
  static int XErrorHandler(Display* dpy, XErrorEvent* error);

  CStopWatch m_screensaverReset;
};

#endif // WINDOW_SYSTEM_H

