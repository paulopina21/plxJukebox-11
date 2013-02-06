#pragma once



#include "windowing/WinEvents.h"

class CWinEventsOSX : public CWinEventsBase
{
public:
  CWinEventsOSX();
  ~CWinEventsOSX();

  static bool MessagePump();
};
