#pragma once


#include "system.h"
#ifdef HAS_FILESYSTEM_SFTP
#include "IDirectory.h"
#include "FileSFTP.h"

class CURL;
class TiXmlElement;

namespace XFILE
{
  class CSFTPDirectory : public IDirectory
  {
  public:
    CSFTPDirectory(void);
    virtual ~CSFTPDirectory(void);
    virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
  };
}
#endif
