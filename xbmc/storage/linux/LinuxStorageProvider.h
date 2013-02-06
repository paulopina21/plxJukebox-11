#pragma once

#include "storage/IStorageProvider.h"
#include "HALProvider.h"
#include "DeviceKitDisksProvider.h"
#include "UDisksProvider.h"
#include "PosixMountProvider.h"

class CLinuxStorageProvider : public IStorageProvider
{
public:
  CLinuxStorageProvider()
  {
    m_instance = NULL;

#ifdef HAS_DBUS
    if (CUDisksProvider::HasUDisks())
      m_instance = new CUDisksProvider();
    else if (CDeviceKitDisksProvider::HasDeviceKitDisks())
      m_instance = new CDeviceKitDisksProvider();
#endif
#ifdef HAS_HAL
    if (m_instance == NULL)
      m_instance = new CHALProvider();
#endif

    if (m_instance == NULL)
      m_instance = new CPosixMountProvider();
  }

  virtual ~CLinuxStorageProvider()
  {
    delete m_instance;
  }

  virtual void Initialize()
  {
    m_instance->Initialize();
  }

  virtual void Stop()
  {
    m_instance->Stop();
  }

  virtual void GetLocalDrives(VECSOURCES &localDrives)
  {
    // Home directory
#ifndef IS_PROFESSIONAL // Laureon: Jukebox: Added: Professional version shouldn't list any system folder
    CMediaSource share;
    share.strPath = getenv("HOME");
    share.strName = g_localizeStrings.Get(21440);
    share.m_ignore = true;
    share.m_iDriveType = CMediaSource::SOURCE_TYPE_LOCAL;
    localDrives.push_back(share);
    share.strPath = "/";
    share.strName = g_localizeStrings.Get(21453);
    localDrives.push_back(share);
#endif

    m_instance->GetLocalDrives(localDrives);
  }

  virtual void GetRemovableDrives(VECSOURCES &removableDrives)
  {
    m_instance->GetRemovableDrives(removableDrives);
  }

  virtual bool Eject(CStdString mountpath)
  {
    return m_instance->Eject(mountpath);
  }

  virtual std::vector<CStdString> GetDiskUsage()
  {
    return m_instance->GetDiskUsage();
  }

  virtual bool PumpDriveChangeEvents(IStorageEventsCallback *callback)
  {
    return m_instance->PumpDriveChangeEvents(callback);
  }

private:
  IStorageProvider *m_instance;
};
