#pragma once



#include "IDirectory.h"

namespace XFILE
{
  class CPlaylistDirectory : public IDirectory
  {
  public:
    CPlaylistDirectory(void);
    virtual ~CPlaylistDirectory(void);
    virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
    virtual bool IsAllowed(const CStdString &strFile) const { return true; };
  };
}
