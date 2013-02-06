
#pragma once
#include "powermanagement/IPowerSyscall.h"
#include "system.h"
#ifdef HAS_HAL

class CHALPowerSyscall : public CPowerSyscallWithoutEvents
{
public:
  CHALPowerSyscall();

  virtual bool Powerdown();
  virtual bool Suspend();
  virtual bool Hibernate();
  virtual bool Reboot();

  virtual bool CanPowerdown();
  virtual bool CanSuspend();
  virtual bool CanHibernate();
  virtual bool CanReboot();
  virtual int  BatteryLevel();

private:
  bool QueryCapability(const char *capability);
  bool doPowerCall(const char *powerstate);

  bool m_CanPowerdown;
  bool m_CanSuspend;
  bool m_CanHibernate;
  bool m_CanReboot;
};
#endif
