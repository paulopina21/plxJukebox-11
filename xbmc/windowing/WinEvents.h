

#ifndef WINDOW_EVENTS_H
#define WINDOW_EVENTS_H

#pragma once

#include "utils/StdString.h"
#include "XBMC_events.h"

typedef bool (* PHANDLE_EVENT_FUNC)(XBMC_Event& newEvent);

class CWinEventsBase
{
public:
  static PHANDLE_EVENT_FUNC m_pEventFunc;
};

#if   defined(TARGET_WINDOWS)
#include "windows/WinEventsWin32.h"
#define CWinEvents CWinEventsWin32

#elif defined(TARGET_DARWIN_OSX)
#include "osx/WinEventsOSX.h"
#define CWinEvents CWinEventsOSX

#elif defined(TARGET_DARWIN_IOS)
#include "osx/WinEventsIOS.h"
#define CWinEvents CWinEventsIOS

#elif defined(TARGET_LINUX) && defined(HAS_SDL_WIN_EVENTS)
#include "WinEventsSDL.h"
#define CWinEvents CWinEventsSDL

#elif defined(TARGET_LINUX) && defined(HAS_LINUX_EVENTS)
#include "WinEventsLinux.h"
#define CWinEvents CWinEventsLinux

#endif

#endif // WINDOW_EVENTS_H
