#pragma once

#include "dbwrappers/Database.h"

class  CFileItem;

#include <set>

enum EACTIVITY{ACTIVITY_SONGS_LAST_REPORT = 1, ACTIVITY_ADVERT_LAST_REPORT = 2};

class CStatsDatabase : public CDatabase {
public:
  CStatsDatabase(void);
  virtual ~CStatsDatabase(void);

  virtual bool Open();
  virtual bool CommitTransaction();
  
  bool LogPlayedItem(CFileItem* pItem);
  bool ExportABLFReport(const CStdString& strPath, bool bRecoverLast = false);
  CStdString GetABLFReport(bool bRecoverLast = false);
  CStdString GetAdvertisingReport(bool bRecoverLast = false);
 
protected:

//  virtual bool Open();
  virtual bool CreateTables();
  virtual void CreateViews();
  virtual bool UpdateOldVersion(int version);

  virtual int GetMinVersion() const {return 0; };
  const char *GetBaseDBName() const {return "Stats";};

private:
//	FILETIME TimeStampToLocalTime( uint64_t timeStamp );
};
