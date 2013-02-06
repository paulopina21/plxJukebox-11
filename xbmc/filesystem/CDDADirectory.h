

#pragma once

#include "IDirectory.h"

namespace XFILE
{

class CCDDADirectory :
      public IDirectory
{
public:
  CCDDADirectory(void);
  virtual ~CCDDADirectory(void);
  virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
};
}
