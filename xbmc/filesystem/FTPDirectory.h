#pragma once


#include "IDirectory.h"

namespace XFILE
{
  class CFTPDirectory : public IDirectory
  {
    public:
      CFTPDirectory(void);
      virtual ~CFTPDirectory(void);
      virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
      virtual bool Exists(const char* strPath);
    private:
  };
}

