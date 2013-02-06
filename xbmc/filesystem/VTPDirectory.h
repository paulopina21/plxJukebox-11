#pragma once


#include "IDirectory.h"

class CVTPSession;

namespace XFILE {

class CVTPDirectory
  : public IDirectory
{
public:
  CVTPDirectory();
  virtual ~CVTPDirectory();

  virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
  virtual bool IsAllowed(const CStdString &strFile) const { return true; };

private:
  bool GetChannels  (const CStdString& base, CFileItemList &items);

  CVTPSession* m_session;
};

}
