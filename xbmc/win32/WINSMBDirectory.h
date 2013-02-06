#pragma once



#include "filesystem/IDirectory.h"
#include "URL.h"

namespace XFILE
{

class CWINSMBDirectory : public IDirectory
{
public:
  CWINSMBDirectory(void);
  virtual ~CWINSMBDirectory(void);
  virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
  virtual DIR_CACHE_TYPE GetCacheType(const CStdString &strPath) const { return DIR_CACHE_ONCE; };
  virtual bool Create(const char* strPath);
  virtual bool Exists(const char* strPath);
  virtual bool Remove(const char* strPath);

  bool ConnectToShare(const CURL& url);
private:
  bool m_bHost;
  bool EnumerateFunc(LPNETRESOURCEW lpnr, CFileItemList &items);
  CStdString GetLocal(const CStdString& strPath);
  CStdString URLEncode(const CURL &url);
};
}
