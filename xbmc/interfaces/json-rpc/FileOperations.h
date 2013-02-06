#pragma once


#include "utils/StdString.h"
#include "JSONRPC.h"
#include "FileItemHandler.h"

namespace JSONRPC
{
  class CFileOperations : public CFileItemHandler
  {
  public:
    static JSON_STATUS GetRootDirectory(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS GetDirectory(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    
    static JSON_STATUS PrepareDownload(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS Download(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);

    static bool FillFileItem(const CFileItemPtr &originalItem, CFileItem &item, CStdString media = "");
    static bool FillFileItemList(const CVariant &parameterObject, CFileItemList &list);
  };
}
