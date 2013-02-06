#pragma once

#include "system.h"
#ifdef HAS_DBUS
#include "DBusMessage.h"
#include "utils/Variant.h"

class CDBusUtil
{
public:
  static CVariant GetAll(const char *destination, const char *object, const char *interface);

  static CVariant GetVariant(const char *destination, const char *object, const char *interface, const char *property);
private:
  static CVariant ParseType(DBusMessageIter *itr);
  static CVariant ParseVariant(DBusMessageIter *itr);
};
#endif
