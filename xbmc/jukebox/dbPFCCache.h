#pragma once

#include "dbwrappers/Database.h"

class  CFileItem;

#include <set>

class dbPFCCache : public CDatabase {
public:
  dbPFCCache(void);
  virtual ~dbPFCCache(void);

  virtual bool Open();
  virtual bool CommitTransaction();
  
  //int addFile(CFileItem& pItem);
  int AddFile(const CStdString& strFullFilePath);
  int AddPath(const CStdString& strPath);

  //bool removeFile(CFileItem& pItem);
  bool RemoveFile(const CStdString& strFile);
  bool RemoveFile(int idFile);

  CStdString GetFile(int idFile);
  CStdString GetFileName(int idFile);
  CStdString GetFilePath(int idFile);

  int GetFilePath(const CStdString& strFileName);
  int GetFilePath(int idFile);

protected:

//  virtual bool Open();
  virtual bool CreateTables();
  virtual void CreateViews();
  virtual bool UpdateOldVersion(int version);

  virtual int GetMinVersion() const {return 1; };
  const char *GetBaseDBName() const {return "filesystem.pfc.cache";};

private:
//	FILETIME TimeStampToLocalTime( uint64_t timeStamp );
};
