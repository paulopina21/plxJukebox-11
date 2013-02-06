#pragma once


#include "IDirectory.h"

namespace XFILE
{
class IFileDirectory : public IDirectory
{
public:
  virtual ~IFileDirectory(void) {};
  virtual bool ContainsFiles(const CStdString& strPath)=0;
};

}
