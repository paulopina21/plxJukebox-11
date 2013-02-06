
#pragma once
#include "system.h"
#include "utils/StdString.h"
#include <vector>

struct DBusConnection;

class CDBusReserve
{
public:
  CDBusReserve();
 ~CDBusReserve();

  bool AcquireDevice(const CStdString &device);
  bool ReleaseDevice(const CStdString &device);

private:
  DBusConnection *m_conn;
  std::vector<CStdString> m_devs;
};

