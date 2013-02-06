#pragma once


#include "utils/StdString.h"
#include "JSONRPC.h"
#include "FileItemHandler.h"

namespace JSONRPC
{
  class CPlaylistOperations : public CFileItemHandler
  {
  public:
    static JSON_STATUS GetPlaylists(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS GetProperties(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);

    static JSON_STATUS GetItems(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS Add(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS Remove(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result); 
    static JSON_STATUS Insert(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS Clear(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS Swap(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
  private:
    static int GetPlaylist(const CVariant &playlist);
    static inline void NotifyAll();
    static JSON_STATUS GetPropertyValue(int playlist, const CStdString &property, CVariant &result);
  };
}
