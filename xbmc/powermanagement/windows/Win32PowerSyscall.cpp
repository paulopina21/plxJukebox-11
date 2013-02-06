

#include "Win32PowerSyscall.h"
#ifdef _WIN32
#include "WIN32Util.h"

bool CWin32PowerSyscall::m_OnResume = false;
bool CWin32PowerSyscall::m_OnSuspend = false;


CWin32PowerSyscall::CWin32PowerSyscall()
{
}

bool CWin32PowerSyscall::Powerdown()
{
  return CWIN32Util::PowerManagement(POWERSTATE_SHUTDOWN);
}
bool CWin32PowerSyscall::Suspend()
{
  // On Vista+, we don't receive the PBT_APMSUSPEND message as we have fired the suspend mode
  // Set the flag manually
  CWin32PowerSyscall::SetOnSuspend();

  return CWIN32Util::PowerManagement(POWERSTATE_SUSPEND);
}
bool CWin32PowerSyscall::Hibernate()
{
  // On Vista+, we don't receive the PBT_APMSUSPEND message as we have fired the suspend mode
  // Set the flag manually
  CWin32PowerSyscall::SetOnSuspend();

  return CWIN32Util::PowerManagement(POWERSTATE_HIBERNATE);
}
bool CWin32PowerSyscall::Reboot()
{
  return CWIN32Util::PowerManagement(POWERSTATE_REBOOT);
}

bool CWin32PowerSyscall::CanPowerdown()
{
  return true;
}
bool CWin32PowerSyscall::CanSuspend()
{
  return true;
}
bool CWin32PowerSyscall::CanHibernate()
{
  return true;
}
bool CWin32PowerSyscall::CanReboot()
{
  return true;
}

int CWin32PowerSyscall::BatteryLevel()
{
  return CWIN32Util::BatteryLevel();
}

bool CWin32PowerSyscall::PumpPowerEvents(IPowerEventsCallback *callback)
{
  if (m_OnSuspend)
  {
    callback->OnSleep();
    m_OnSuspend = false;
    return true;
  }
  else if (m_OnResume)
  {
    callback->OnWake();
    m_OnResume = false;
    return true;
  }
  else
    return false;
}
#endif
