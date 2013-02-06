

#ifndef WINDOW_EVENTS_WIN32_H
#define WINDOW_EVENTS_WIN32_H

#pragma once

#include "WinEvents.h"

class CWinEventsWin32 : public CWinEventsBase
{
public:
  static bool MessagePump();
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
  static void RegisterDeviceInterfaceToHwnd(GUID InterfaceClassGuid, HWND hWnd, HDEVNOTIFY *hDeviceNotify);
  static void WindowFromScreenCoords(HWND hWnd, POINT *point);
  static void OnGestureNotify(HWND hWnd, LPARAM lParam);
  static void OnGesture(HWND hWnd, LPARAM lParam);

  static int m_lastGesturePosX;
  static int m_lastGesturePosY;
};

#endif // WINDOW_EVENTS_WIN32_H
