#pragma once


#include "MediaSource.h" // for VECSOURCES
#include <map>
#ifdef HAS_DVD_DRIVE
#include "cdioSupport.h"
#endif
#include "URL.h"
#include "utils/Job.h"
#include "IStorageProvider.h"
#include "threads/CriticalSection.h"

#ifdef HAS_DVD_DRIVE
using namespace MEDIA_DETECT;
#endif

class CNetworkLocation
{
public:
  CNetworkLocation() { id = 0; };
  int id;
  CStdString path;
};

class CMediaManager : public IStorageEventsCallback, public IJobCallback
{
public:
  CMediaManager();

  void Initialize();
  void Stop();

  bool LoadSources();
  bool SaveSources();

  void GetLocalDrives(VECSOURCES &localDrives, bool includeQ = true);
  void GetRemovableDrives(VECSOURCES &removableDrives);
  void GetNetworkLocations(VECSOURCES &locations, bool autolocations = true);

  bool AddNetworkLocation(const CStdString &path);
  bool HasLocation(const CStdString& path) const;
  bool RemoveLocation(const CStdString& path);
  bool SetLocationPath(const CStdString& oldPath, const CStdString& newPath);

  void AddAutoSource(const CMediaSource &share, bool bAutorun=false);
  void RemoveAutoSource(const CMediaSource &share);
  bool IsDiscInDrive(const CStdString& devicePath="");
  bool IsAudio(const CStdString& devicePath="");
  CStdString TranslateDevicePath(const CStdString& devicePath, bool bReturnAsDevice=false);
  DWORD GetDriveStatus(const CStdString& devicePath="");
#ifdef HAS_DVD_DRIVE
  CCdInfo* GetCdInfo(const CStdString& devicePath="");
  bool RemoveCdInfo(const CStdString& devicePath="");
  CStdString GetDiskLabel(const CStdString& devicePath="");
  CStdString GetDiskUniqueId(const CStdString& devicePath="");
#endif
  CStdString GetDiscPath();
  void SetHasOpticalDrive(bool bstatus);

  bool Eject(CStdString mountpath);

  void ProcessEvents();

  std::vector<CStdString> GetDiskUsage();

  virtual void OnStorageAdded(const CStdString &label, const CStdString &path);
  virtual void OnStorageSafelyRemoved(const CStdString &label);
  virtual void OnStorageUnsafelyRemoved(const CStdString &label);

  virtual void OnJobComplete(unsigned int jobID, bool success, CJob *job) { }
protected:
  std::vector<CNetworkLocation> m_locations;

  CCriticalSection m_muAutoSource, m_CritSecStorageProvider;
#ifdef HAS_DVD_DRIVE
  std::map<CStdString,CCdInfo*> m_mapCdInfo;
  bool HashDVD(const CStdString& dvdpath, uint32_t& crc);
#endif
  bool m_bhasoptical;

private:
  IStorageProvider *m_platformStorage;
};

extern class CMediaManager g_mediaManager;

