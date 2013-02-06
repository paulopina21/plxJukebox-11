#pragma once


#include "IDirectory.h"

namespace XFILE
{
  class CMusicSearchDirectory : public IDirectory
  {
  public:
    CMusicSearchDirectory(void);
    virtual ~CMusicSearchDirectory(void);
    virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
    virtual bool Exists(const char* strPath);
    virtual bool IsAllowed(const CStdString &strFile) const { return true; };
  };
}
