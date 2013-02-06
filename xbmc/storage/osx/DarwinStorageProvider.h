#pragma once

#include "utils/StdString.h"
#include "storage/IStorageProvider.h"

class CDarwinStorageProvider : public IStorageProvider
{
public:
  CDarwinStorageProvider();
  virtual ~CDarwinStorageProvider() { }

  virtual void Initialize() { }
  virtual void Stop() { }

  virtual void GetLocalDrives(VECSOURCES &localDrives);
  virtual void GetRemovableDrives(VECSOURCES &removableDrives);

  virtual std::vector<CStdString> GetDiskUsage(void);

  virtual bool Eject(CStdString mountpath);

  virtual bool PumpDriveChangeEvents(IStorageEventsCallback *callback);

  static void SetEvent(void);

private:
  static bool m_event;
};
