
#include "Win32StorageProvider.h"
#include "WIN32Util.h"
#include "guilib/LocalizeStrings.h"
#include "filesystem/SpecialProtocol.h"
#include "storage/MediaManager.h"
#include "utils/JobManager.h"

bool CWin32StorageProvider::event = false;

void CWin32StorageProvider::Initialize()
{
  // check for a DVD drive
  VECSOURCES vShare;
  CWIN32Util::GetDrivesByType(vShare, DVD_DRIVES);
  if(!vShare.empty())
    g_mediaManager.SetHasOpticalDrive(true);

  // Can be removed once the StorageHandler supports optical media
  VECSOURCES::const_iterator it;
  for(it=vShare.begin();it!=vShare.end();++it)
    if(g_mediaManager.GetDriveStatus(it->strPath) == DRIVE_CLOSED_MEDIA_PRESENT)
      CJobManager::GetInstance().AddJob(new CDetectDisc(it->strPath, false), NULL);
  // remove end
}

void CWin32StorageProvider::GetLocalDrives(VECSOURCES &localDrives)
{
#ifndef IS_JUKEBOX // Laureon: Added: Jukebox shouldn't show the home folder in file listings.. 
  CMediaSource share;
  share.strPath = _P("special://home");
  share.strName = g_localizeStrings.Get(21440);
  share.m_ignore = true;
  share.m_iDriveType = CMediaSource::SOURCE_TYPE_LOCAL;
  localDrives.push_back(share);
#endif
  CWIN32Util::GetDrivesByType(localDrives, LOCAL_DRIVES);
}

void CWin32StorageProvider::GetRemovableDrives(VECSOURCES &removableDrives)
{
  CWIN32Util::GetDrivesByType(removableDrives, REMOVABLE_DRIVES, true);
}

bool CWin32StorageProvider::Eject(CStdString mountpath)
{
  if (!mountpath.IsEmpty())
  {
    return CWIN32Util::EjectDrive(mountpath[0]);
  }
  return false;
}

std::vector<CStdString> CWin32StorageProvider::GetDiskUsage()
{
  return CWIN32Util::GetDiskUsage();
}

bool CWin32StorageProvider::PumpDriveChangeEvents(IStorageEventsCallback *callback)
{
  bool b = event;
  event = false;
  return b;
}

CDetectDisc::CDetectDisc(const CStdString &strPath, const bool bautorun)
  : m_strPath(strPath), m_bautorun(bautorun)
{
}

bool CDetectDisc::DoWork()
{
  CMediaSource share;
  share.strPath = m_strPath;
  share.strStatus = g_mediaManager.GetDiskLabel(share.strPath);
  share.strDiskUniqueId = g_mediaManager.GetDiskUniqueId(share.strPath);
  if(g_mediaManager.IsAudio(share.strPath))
    share.strStatus = "Audio-CD";
  else if(share.strStatus == "")
    share.strStatus = g_localizeStrings.Get(446);
  share.strName = share.strPath;
  share.m_ignore = true;
  share.m_iDriveType = CMediaSource::SOURCE_TYPE_DVD;
  g_mediaManager.AddAutoSource(share, m_bautorun);
  return true;
}
