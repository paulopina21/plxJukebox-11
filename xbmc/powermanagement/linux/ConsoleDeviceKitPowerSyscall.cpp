

#include "system.h"
#include "ConsoleDeviceKitPowerSyscall.h"
#include "utils/log.h"

#ifdef HAS_DBUS
#include "Application.h"
#include "DBusUtil.h"

CConsoleDeviceKitPowerSyscall::CConsoleDeviceKitPowerSyscall()
{
  m_CanPowerdown = ConsoleKitMethodCall("CanStop");
  m_CanSuspend   = CDBusUtil::GetVariant("org.freedesktop.DeviceKit.Power", "/org/freedesktop/DeviceKit/Power",    "org.freedesktop.DeviceKit.Power", "can_suspend").asBoolean();
  m_CanHibernate = CDBusUtil::GetVariant("org.freedesktop.DeviceKit.Power", "/org/freedesktop/DeviceKit/Power",    "org.freedesktop.DeviceKit.Power", "can_hibernate").asBoolean();
  m_CanReboot    = ConsoleKitMethodCall("CanRestart");
}

bool CConsoleDeviceKitPowerSyscall::Powerdown()
{
  CDBusMessage message("org.freedesktop.ConsoleKit", "/org/freedesktop/ConsoleKit/Manager", "org.freedesktop.ConsoleKit.Manager", "Stop");
  return message.SendSystem() != NULL;
}

bool CConsoleDeviceKitPowerSyscall::Suspend()
{
  CPowerSyscallWithoutEvents::Suspend();

  CDBusMessage message("org.freedesktop.DeviceKit.Power", "/org/freedesktop/DeviceKit/Power", "org.freedesktop.DeviceKit.Power", "Suspend");
  return message.SendAsyncSystem();
}

bool CConsoleDeviceKitPowerSyscall::Hibernate()
{
  CPowerSyscallWithoutEvents::Hibernate();

  CDBusMessage message("org.freedesktop.DeviceKit.Power", "/org/freedesktop/DeviceKit/Power", "org.freedesktop.DeviceKit.Power", "Hibernate");
  return message.SendAsyncSystem();
}

bool CConsoleDeviceKitPowerSyscall::Reboot()
{
  CDBusMessage message("org.freedesktop.ConsoleKit", "/org/freedesktop/ConsoleKit/Manager", "org.freedesktop.ConsoleKit.Manager", "Restart");
  return message.SendSystem() != NULL;
}

bool CConsoleDeviceKitPowerSyscall::CanPowerdown()
{
  return m_CanPowerdown;
}
bool CConsoleDeviceKitPowerSyscall::CanSuspend()
{
  return m_CanSuspend;
}
bool CConsoleDeviceKitPowerSyscall::CanHibernate()
{
  return m_CanHibernate;
}
bool CConsoleDeviceKitPowerSyscall::CanReboot()
{
  return m_CanReboot;
}

int CConsoleDeviceKitPowerSyscall::BatteryLevel()
{
  return 0;
}

bool CConsoleDeviceKitPowerSyscall::HasDeviceConsoleKit()
{
  bool hasConsoleKitManager = false;
  CDBusMessage consoleKitMessage("org.freedesktop.ConsoleKit", "/org/freedesktop/ConsoleKit/Manager", "org.freedesktop.ConsoleKit.Manager", "CanStop");

  DBusError error;
  dbus_error_init (&error);
  DBusConnection *con = dbus_bus_get(DBUS_BUS_SYSTEM, &error);

  if (dbus_error_is_set(&error))
  {
    CLog::Log(LOGDEBUG, "ConsoleUPowerSyscall: %s - %s", error.name, error.message);
    dbus_error_free(&error);
    return false;
  }

  consoleKitMessage.Send(con, &error);

  if (!dbus_error_is_set(&error))
    hasConsoleKitManager = true;
  else
    CLog::Log(LOGDEBUG, "ConsoleKit.Manager: %s - %s", error.name, error.message);

  dbus_error_free (&error);

  bool hasDeviceKitPower = false;
  CDBusMessage deviceKitMessage("org.freedesktop.DeviceKit.Disks", "/org/freedesktop/DeviceKit/Disks", "org.freedesktop.DeviceKit.Disks", "EnumerateDevices");

  deviceKitMessage.Send(con, &error);

  if (!dbus_error_is_set(&error))
    hasDeviceKitPower = true;
  else
    CLog::Log(LOGDEBUG, "DeviceKit.Power: %s - %s", error.name, error.message);

  dbus_error_free (&error);
  dbus_connection_unref(con);

  return hasDeviceKitPower && hasConsoleKitManager;
}

bool CConsoleDeviceKitPowerSyscall::ConsoleKitMethodCall(const char *method)
{
  CDBusMessage message("org.freedesktop.ConsoleKit", "/org/freedesktop/ConsoleKit/Manager", "org.freedesktop.ConsoleKit.Manager", method);
  DBusMessage *reply = message.SendSystem();
  if (reply)
  {
    dbus_bool_t boolean = FALSE;

    if (dbus_message_get_args (reply, NULL, DBUS_TYPE_BOOLEAN, &boolean, DBUS_TYPE_INVALID))
      return boolean;
  }

  return false;
}
#endif
