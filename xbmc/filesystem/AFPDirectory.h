#pragma once


#include "IDirectory.h"
#include "MediaSource.h"
#include "URL.h"

struct afp_file_info;

namespace XFILE
{
class CAFPDirectory : public IDirectory
{
public:
  CAFPDirectory(void);
  virtual ~CAFPDirectory(void);
  virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
  virtual DIR_CACHE_TYPE GetCacheType(const CStdString &strPath) const { return DIR_CACHE_ONCE; };
  virtual bool Create(const char* strPath);
  virtual bool Exists(const char* strPath);
  virtual bool Remove(const char* strPath);

  afp_file_info *Open(const CURL &url);
private:
  afp_file_info *OpenDir(const CURL &url, CStdString& strAuth);
  bool ResolveSymlink( const CStdString &dirName, const CStdString &fileName, 
                       struct stat *stat, CURL &resolvedUrl);
};
}
