

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _WIN32
#ifndef _WIN32_POWER_SYSCALL_H_
#define _WIN32_POWER_SYSCALL_H_
#include "powermanagement/IPowerSyscall.h"

class CWin32PowerSyscall : public IPowerSyscall
{
public:
  CWin32PowerSyscall();

  virtual bool Powerdown();
  virtual bool Suspend();
  virtual bool Hibernate();
  virtual bool Reboot();

  virtual bool CanPowerdown();
  virtual bool CanSuspend();
  virtual bool CanHibernate();
  virtual bool CanReboot();
  virtual int  BatteryLevel();

  virtual bool PumpPowerEvents(IPowerEventsCallback *callback);

  static void SetOnResume() { m_OnResume = true; }
  static void SetOnSuspend() { m_OnSuspend = true; }

private:

  static bool m_OnResume;
  static bool m_OnSuspend;

};
#endif
#endif
