

#ifdef HAS_DBUS
#include "powermanagement/IPowerSyscall.h"
#include "DBusUtil.h"
#include "utils/StdString.h"

#include <list>

class CUPowerSource
{
public:
  CUPowerSource(const char *powerSource);
  ~CUPowerSource();

  void    Update();
  bool    IsRechargeable();
  double  BatteryLevel();

private:
  CStdString m_powerSource;
  bool m_isRechargeable;
  double m_batteryLevel;
};

class CConsoleUPowerSyscall : public IPowerSyscall
{
public:
  CConsoleUPowerSyscall();
  virtual ~CConsoleUPowerSyscall();

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

  static bool HasDeviceConsoleKit();
private:
  static bool ConsoleKitMethodCall(const char *method);
  void UpdateUPower();

  bool m_CanPowerdown;
  bool m_CanSuspend;
  bool m_CanHibernate;
  bool m_CanReboot;

  bool m_lowBattery;

  void EnumeratePowerSources();
  std::list<CUPowerSource> m_powerSources;

  DBusConnection *m_connection;
  DBusError m_error;
};
#endif
