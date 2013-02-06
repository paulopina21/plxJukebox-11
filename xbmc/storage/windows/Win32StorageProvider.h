#pragma once

#include "storage/IStorageProvider.h"
#include "utils/Job.h"

class CWin32StorageProvider : public IStorageProvider
{
public:
  virtual ~CWin32StorageProvider() { }

  virtual void Initialize();
  virtual void Stop() { }

  virtual void GetLocalDrives(VECSOURCES &localDrives);
  virtual void GetRemovableDrives(VECSOURCES &removableDrives);

  virtual bool Eject(CStdString mountpath);

  virtual std::vector<CStdString> GetDiskUsage();

  virtual bool PumpDriveChangeEvents(IStorageEventsCallback *callback);

  static void SetEvent() { event = true; }
  static bool event;
};

class CDetectDisc : public CJob
{
public:
  CDetectDisc(const CStdString &strPath, const bool bautorun);
  bool DoWork();

private:
  CStdString  m_strPath;
  bool        m_bautorun;
};

