

#ifndef _POWER_MANAGER_H_
#define _POWER_MANAGER_H_
#include "IPowerSyscall.h"

// For systems without PowerSyscalls we have a NullObject
class CNullPowerSyscall : public IPowerSyscall
{
public:
  virtual bool Powerdown()    { return false; }
  virtual bool Suspend()      { return false; }
  virtual bool Hibernate()    { return false; }
  virtual bool Reboot()       { return false; }

  virtual bool CanPowerdown() { return true; }
  virtual bool CanSuspend()   { return true; }
  virtual bool CanHibernate() { return true; }
  virtual bool CanReboot()    { return true; }

  virtual int  BatteryLevel() { return 0; }


  virtual bool PumpPowerEvents(IPowerEventsCallback *callback) { return false; }
};

// This class will wrap and handle PowerSyscalls.
// It will handle and decide if syscalls are needed.
class CPowerManager : public IPowerEventsCallback
{
public:
  CPowerManager();
  ~CPowerManager();

  void Initialize();
  void SetDefaults();

  bool Powerdown();
  bool Suspend();
  bool Hibernate();
  bool Reboot();

  bool CanPowerdown();
  bool CanSuspend();
  bool CanHibernate();
  bool CanReboot();
  
  int  BatteryLevel();

  void ProcessEvents();
private:
  void OnSleep();
  void OnWake();

  void OnLowBattery();

  IPowerSyscall *m_instance;
};

extern CPowerManager g_powerManager;
#endif
