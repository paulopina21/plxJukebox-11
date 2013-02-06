#pragma once



#include "IFileDirectory.h"

namespace XFILE
{
  class CRarDirectory : public IFileDirectory
  {
  public:
    CRarDirectory();
    ~CRarDirectory();
    virtual bool GetDirectory(const CStdString& strPath, CFileItemList& items);
    virtual bool ContainsFiles(const CStdString& strPath);
    virtual bool Exists(const char* strPath);
    virtual DIR_CACHE_TYPE GetCacheType(const CStdString& strPath) const { return DIR_CACHE_ALWAYS; };
  };
}
