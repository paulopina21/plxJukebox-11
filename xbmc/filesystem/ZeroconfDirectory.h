
#pragma once
#include "IDirectory.h"
//txt-records as of http://www.dns-sd.org/ServiceTypes.html
#define TXT_RECORD_PATH_KEY     "path"
#define TXT_RECORD_USERNAME_KEY "u"
#define TXT_RECORD_PASSWORD_KEY "p"

namespace XFILE
{
  class CZeroconfDirectory : public IDirectory
  {
    public:
      CZeroconfDirectory(void);
      virtual ~CZeroconfDirectory(void);
      virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
      virtual DIR_CACHE_TYPE GetCacheType(const CStdString& strPath) const { return DIR_CACHE_NEVER; };
  };
}

