

#pragma once

#ifndef WINDOW_EVENTS_IOS_H
#define WINDOW_EVENTS_IOS_H

#include "windowing/WinEvents.h"

class CWinEventsIOS : public CWinEventsBase
{
public:
  static void Init();
  static void DeInit();
  static void MessagePush(XBMC_Event *newEvent);
  static bool MessagePump();

protected:
};

#endif // WINDOW_EVENTS_IOS_H
