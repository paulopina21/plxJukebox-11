#pragma once

#include "dbwrappers/Database.h"

#include <set>

class CProfessionalDatabase : public CDatabase {
public:
  CProfessionalDatabase(void);
  virtual ~CProfessionalDatabase(void);

  virtual bool Open();
  virtual bool CommitTransaction();
  
  bool AddCoin(int iAmount = 1);
  bool RemoveCoin(int iAmount = 1);
  int GetCoins();
 
protected:

//  virtual bool Open();
  virtual bool CreateTables();
  virtual void CreateViews();
  virtual bool UpdateOldVersion(int version);

  virtual int GetMinVersion() const {return 0; };
  const char *GetBaseDBName() const {return "Jukebox";};

private:
//	FILETIME TimeStampToLocalTime( uint64_t timeStamp );
};
