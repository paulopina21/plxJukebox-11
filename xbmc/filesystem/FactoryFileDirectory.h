#pragma once


#include "IFileDirectory.h"

class CFileItem;

namespace XFILE
{
class CFactoryFileDirectory
{
public:
  CFactoryFileDirectory(void);
  virtual ~CFactoryFileDirectory(void);
  static IFileDirectory* Create(const CStdString& strPath, CFileItem* pItem, const CStdString& strMask="");
};
}
