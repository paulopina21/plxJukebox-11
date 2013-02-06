#pragma once


#include "IDirectory.h"

namespace XFILE
{
  class CHTTPDirectory : public IDirectory
  {
    public:
      CHTTPDirectory(void);
      virtual ~CHTTPDirectory(void);
      virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
      virtual bool Exists(const char* strPath);
      virtual DIR_CACHE_TYPE GetCacheType(const CStdString& strPath) const { return DIR_CACHE_ONCE; };
    private:
  };
}
