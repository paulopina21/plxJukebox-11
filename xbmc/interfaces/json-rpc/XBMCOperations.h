#pragma once


#include "utils/StdString.h"
#include "JSONRPC.h"

namespace JSONRPC
{
  class CXBMCOperations
  {
  public:
    static JSON_STATUS GetInfoLabels(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS GetInfoBooleans(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
  };
}
