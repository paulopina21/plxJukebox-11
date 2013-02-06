

#ifndef CRSSDIRECTORY_H_
#define CRSSDIRECTORY_H_

#include "IFileDirectory.h"
#include "FileItem.h"

namespace XFILE
{
  class CRSSDirectory : public IFileDirectory
  {
  public:
    CRSSDirectory();
    virtual ~CRSSDirectory();
    virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
    virtual bool Exists(const char* strPath);
    virtual bool IsAllowed(const CStdString &strFile) const { return true; };
    virtual bool ContainsFiles(const CStdString& strPath);
    virtual DIR_CACHE_TYPE GetCacheType(const CStdString& strPath) const { return DIR_CACHE_ONCE; };
  protected:
    // key is path, value is cache invalidation date
    static std::map<CStdString,CDateTime> m_cache;
    static CCriticalSection m_section;
  };
}

#endif /*CRSSDIRECTORY_H_*/
