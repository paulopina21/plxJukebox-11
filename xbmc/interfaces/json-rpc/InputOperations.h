#pragma once


#include "JSONRPC.h"
#include "threads/CriticalSection.h"
#include "utils/StdString.h"

namespace JSONRPC
{
  class CInputOperations
  {
  public:
    static uint32_t GetKey();

    static JSON_STATUS Left(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS Right(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS Down(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS Up(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);

    static JSON_STATUS Select(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);

    static JSON_STATUS Back(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);

    static JSON_STATUS Home(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);

  private:
    static JSON_STATUS sendKey(uint32_t keyCode);
    static JSON_STATUS sendAction(int actionID);
    static JSON_STATUS activateWindow(int windowID);
    static bool        handleScreenSaver();

    static CCriticalSection m_critSection;
    static uint32_t m_key;
  };
}
