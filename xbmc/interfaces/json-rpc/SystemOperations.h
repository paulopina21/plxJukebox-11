#pragma once


#include "utils/StdString.h"
#include "JSONRPC.h"

namespace JSONRPC
{
  class CSystemOperations
  {
  public:
    static JSON_STATUS GetProperties(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);

    static JSON_STATUS Shutdown(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS Suspend(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS Hibernate(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS Reboot(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
  private:
    static JSON_STATUS GetPropertyValue(int permissions, const CStdString &property, CVariant &result);
  };
}
