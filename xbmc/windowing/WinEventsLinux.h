

#ifndef WINDOW_EVENTS_LINUX_H
#define WINDOW_EVENTS_LINUX_H

#pragma once
#include "windowing/WinEvents.h"
#include "input/linux/LinuxInputDevices.h"

class CWinEventsLinux : public CWinEventsBase
{
public:
  CWinEventsLinux();
  static bool MessagePump();
  static void RefreshDevices();
  static bool IsRemoteLowBattery();

private:
  static bool m_initialized;
  static CLinuxInputDevices m_devices;
};

#endif
