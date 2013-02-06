
#pragma once

#ifndef WINDOW_EVENTS_SDL_H
#define WINDOW_EVENTS_SDL_H

#ifdef HAS_SDL
#include <SDL/SDL_events.h>

#include "WinEvents.h"

class CWinEventsSDL : public CWinEventsBase
{
public:
  static bool MessagePump();

protected:
#ifdef __APPLE__
  static bool ProcessOSXShortcuts(SDL_Event& event);
#elif defined(_LINUX)
  static bool ProcessLinuxShortcuts(SDL_Event& event);
#endif
};

#endif
#endif // WINDOW_EVENTS_SDL_H
