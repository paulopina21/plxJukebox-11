
#include "HALProvider.h"
#ifdef HAS_HAL
#include "HALManager.h"
#include "utils/log.h"
#include "PosixMountProvider.h"

CHALProvider::CHALProvider()
{
  m_removableLength = 0;
}

void CHALProvider::Initialize()
{
  CLog::Log(LOGDEBUG, "Selected HAL as storage provider");
  g_HalManager.Initialize();
  PumpDriveChangeEvents(NULL);
}

void CHALProvider::Stop()
{
  g_HalManager.Stop();
}

void CHALProvider::GetLocalDrives(VECSOURCES &localDrives)
{
  std::vector<CStorageDevice> devices = g_HalManager.GetVolumeDevices();

  for (size_t i = 0; i < devices.size(); i++)
  {
    if (devices[i].Mounted && devices[i].Approved && !devices[i].HotPlugged)
    {
      CMediaSource share;
      devices[i].toMediaSource(&share);
      localDrives.push_back(share);
    }
  }
}

void CHALProvider::GetRemovableDrives(VECSOURCES &removableDrives)
{
  std::vector<CStorageDevice> devices = g_HalManager.GetVolumeDevices();

  for (size_t i = 0; i < devices.size(); i++)
  {
    if (devices[i].Mounted && devices[i].Approved && devices[i].HotPlugged)
    {
      CMediaSource share;
      devices[i].toMediaSource(&share);
      removableDrives.push_back(share);
    }
  }
}

bool CHALProvider::Eject(CStdString mountpath)
{
  return g_HalManager.Eject(mountpath);
}

std::vector<CStdString> CHALProvider::GetDiskUsage()
{
  CPosixMountProvider legacy;
  return legacy.GetDiskUsage();
}

// TODO Use HALs events for this instead.
bool CHALProvider::PumpDriveChangeEvents(IStorageEventsCallback *callback)
{
//Pump HalManager dry of events
  bool changed = false;
  while (g_HalManager.Update())
    changed = true;

  return changed;
}
#endif
