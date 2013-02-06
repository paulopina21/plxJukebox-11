#pragma once



#include "IFileDirectory.h"

namespace XFILE
{
  class CSmartPlaylistDirectory : public IFileDirectory
  {
  public:
    CSmartPlaylistDirectory();
    ~CSmartPlaylistDirectory();
    virtual bool GetDirectory(const CStdString& strPath, CFileItemList& items);
    virtual bool IsAllowed(const CStdString &strFile) const { return true; };
    virtual bool ContainsFiles(const CStdString& strPath);
    virtual bool Remove(const char *strPath);

    static CStdString GetPlaylistByName(const CStdString& name, const CStdString& playlistType);
  };
}
