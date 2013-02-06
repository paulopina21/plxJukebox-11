#pragma once


#include "IDirectory.h"
#include "FileNFS.h"

namespace XFILE
{
  class CNFSDirectory : public IDirectory
  {
    public:
      CNFSDirectory(void);
      virtual ~CNFSDirectory(void);
      virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
      virtual DIR_CACHE_TYPE GetCacheType(const CStdString &strPath) const { return DIR_CACHE_ONCE; };
      virtual bool Create(const char* strPath);
      virtual bool Exists(const char* strPath);
      virtual bool Remove(const char* strPath);
    private:
      bool GetServerList(CFileItemList &items);
      bool GetDirectoryFromExportList(const CStdString& strPath, CFileItemList &items);
      bool ResolveSymlink( const CStdString &dirName, struct nfsdirent *dirent, CURL &resolvedUrl);
  };
}

