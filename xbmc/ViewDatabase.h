#pragma once

#include "dbwrappers/Database.h"

class CViewState;

class CViewDatabase : public CDatabase
{
public:
  CViewDatabase(void);
  virtual ~CViewDatabase(void);
  virtual bool Open();

  bool GetViewState(const CStdString &path, int windowID, CViewState &state, const CStdString &skin);
  bool SetViewState(const CStdString &path, int windowID, const CViewState &state, const CStdString &skin);
  bool ClearViewStates(int windowID);

protected:
  virtual bool CreateTables();
  virtual bool UpdateOldVersion(int version);
  virtual int GetMinVersion() const { return 4; };
  const char *GetBaseDBName() const { return "ViewModes"; };
};
