
#include "system.h"

#if defined(HAS_LINUX_EVENTS)

#include "WinEventsLinux.h"
#include "WinEvents.h"
#include "XBMC_events.h"
#include "input/XBMC_keysym.h"
#include "Application.h"
#include "input/MouseStat.h"
#include "utils/log.h"
#include "powermanagement/PowerManager.h"

PHANDLE_EVENT_FUNC CWinEventsBase::m_pEventFunc = NULL;

bool CWinEventsLinux::m_initialized = false;
CLinuxInputDevices CWinEventsLinux::m_devices;

CWinEventsLinux::CWinEventsLinux()
{
}

void CWinEventsLinux::RefreshDevices()
{
  m_devices.InitAvailable();
}

bool CWinEventsLinux::IsRemoteLowBattery()
{
  return m_devices.IsRemoteLowBattery();
  return false;
}

bool CWinEventsLinux::MessagePump()
{
  if (!m_initialized)
  {
    m_devices.InitAvailable();
    m_initialized = true;
  }

  bool ret = false;
  XBMC_Event event = {0};
  while (1)
  {
    event = m_devices.ReadEvent();
    if (event.type != XBMC_NOEVENT)
    {
      ret |= g_application.OnEvent(event);
    }
    else
    {
      break;
    }
  }

  return ret;
}

#endif
