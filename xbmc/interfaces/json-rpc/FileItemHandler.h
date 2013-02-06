#pragma once


#include "utils/StdString.h"
#include "JSONRPC.h"
#include "JSONUtils.h"
#include "FileItem.h"

namespace JSONRPC
{
  class CFileItemHandler : public CJSONUtils
  {
  protected:
    static void FillDetails(ISerializable* info, CFileItemPtr item, const CVariant& fields, CVariant &result);
    static void HandleFileItemList(const char *ID, bool allowFile, const char *resultname, CFileItemList &items, const CVariant &parameterObject, CVariant &result);
    static void HandleFileItem(const char *ID, bool allowFile, const char *resultname, CFileItemPtr item, const CVariant &parameterObject, const CVariant &validFields, CVariant &result, bool append = true);

    static bool FillFileItemList(const CVariant &parameterObject, CFileItemList &list);
  private:
    static bool ParseSortMethods(const CStdString &method, const bool &ignorethe, const CStdString &order, SORT_METHOD &sortmethod, SORT_ORDER &sortorder);
    static void Sort(CFileItemList &items, const CVariant& parameterObject);
  };
}
