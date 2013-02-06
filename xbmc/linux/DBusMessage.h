#pragma once

#include "system.h"
#ifdef HAS_DBUS
#include <dbus/dbus.h>

class CDBusMessage
{
public:
  CDBusMessage(const char *destination, const char *object, const char *interface, const char *method);
  ~CDBusMessage();

  bool AppendObjectPath(const char *object);
  bool AppendArgument(const char *string);
  bool AppendArgument(const char **arrayString, unsigned int length);

  DBusMessage *SendSystem();
  DBusMessage *SendSession();

  bool SendAsyncSystem();
  bool SendAsyncSession();

  DBusMessage *Send(DBusBusType type);
  DBusMessage *Send(DBusConnection *con, DBusError *error);
private:

  bool SendAsync(DBusBusType type);

  void Close();
  void PrepareArgument();

  DBusMessage *m_message;
  DBusMessage *m_reply;
  DBusMessageIter m_args;
  bool m_haveArgs;
};
#endif
