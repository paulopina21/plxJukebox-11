

#include "SystemOperations.h"
#include "Application.h"
#include "utils/Variant.h"
#include "powermanagement/PowerManager.h"

using namespace JSONRPC;

JSON_STATUS CSystemOperations::GetProperties(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result)
{
  CVariant properties = CVariant(CVariant::VariantTypeObject);
  for (unsigned int index = 0; index < parameterObject["properties"].size(); index++)
  {
    CStdString propertyName = parameterObject["properties"][index].asString();
    CVariant property;
    JSON_STATUS ret;
    if ((ret = GetPropertyValue(client->GetPermissionFlags(), propertyName, property)) != OK)
      return ret;

    properties[propertyName] = property;
  }

  result = properties;

  return OK;
}

JSON_STATUS CSystemOperations::Shutdown(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result)
{
  if (g_powerManager.CanPowerdown())
  {
    g_application.getApplicationMessenger().Powerdown();
    return ACK;
  }
  else
    return FailedToExecute;
}

JSON_STATUS CSystemOperations::Suspend(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result)
{
  if (g_powerManager.CanSuspend())
  {
    g_application.getApplicationMessenger().Suspend();
    return ACK;
  }
  else
    return FailedToExecute;
}

JSON_STATUS CSystemOperations::Hibernate(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result)
{
  if (g_powerManager.CanHibernate())
  {
    g_application.getApplicationMessenger().Hibernate();
    return ACK;
  }
  else
    return FailedToExecute;
}

JSON_STATUS CSystemOperations::Reboot(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result)
{
  if (g_powerManager.CanReboot())
  {
    g_application.getApplicationMessenger().Restart();
    return ACK;
  }
  else
    return FailedToExecute;
}

JSON_STATUS CSystemOperations::GetPropertyValue(int permissions, const CStdString &property, CVariant &result)
{
  if (property.Equals("canshutdown"))
    result = g_powerManager.CanPowerdown() && (permissions & ControlPower);
  else if (property.Equals("cansuspend"))
    result = g_powerManager.CanSuspend() && (permissions & ControlPower);
  else if (property.Equals("canhibernate"))
    result = g_powerManager.CanHibernate() && (permissions & ControlPower);
  else if (property.Equals("canreboot"))
    result = g_powerManager.CanReboot() && (permissions & ControlPower);
  else
    return InvalidParams;

  return OK;
}
