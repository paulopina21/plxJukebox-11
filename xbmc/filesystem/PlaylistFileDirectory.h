#pragma once



#include "IFileDirectory.h"

namespace XFILE
{
  class CPlaylistFileDirectory : public IFileDirectory
  {
  public:
    CPlaylistFileDirectory();
    ~CPlaylistFileDirectory();
    virtual bool GetDirectory(const CStdString& strPath, CFileItemList& items);
    virtual bool ContainsFiles(const CStdString& strPath);
    virtual bool Remove(const char *strPath);
    virtual bool IsAllowed(const CStdString &strFile) const { return true; };
  };
}
