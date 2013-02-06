

#include "SourcesDirectory.h"
#include "utils/URIUtils.h"
#include "URL.h"
#include "Util.h"
#include "FileItem.h"
#include "File.h"
#include "settings/Settings.h"
#include "guilib/TextureManager.h"
#include "storage/MediaManager.h"

using namespace XFILE;

CSourcesDirectory::CSourcesDirectory(void)
{
}

CSourcesDirectory::~CSourcesDirectory(void)
{
}

bool CSourcesDirectory::GetDirectory(const CStdString& strPath, CFileItemList &items)
{
  // break up our path
  // format is:  sources://<type>/
  CURL url(strPath);
  CStdString type(url.GetFileName());
  URIUtils::RemoveSlashAtEnd(type);

  VECSOURCES sources;
  VECSOURCES *sourcesFromType = g_settings.GetSourcesFromType(type);
  if (sourcesFromType)
    sources = *sourcesFromType;
  g_mediaManager.GetRemovableDrives(sources);

  if (sources.empty())
    return false;

  return GetDirectory(sources, items);
}

bool CSourcesDirectory::GetDirectory(const VECSOURCES &sources, CFileItemList &items)
{
  for (unsigned int i = 0; i < sources.size(); ++i)
  {
    const CMediaSource& share = sources[i];
    CFileItemPtr pItem(new CFileItem(share));
    if (pItem->IsLastFM() || (pItem->GetPath().Left(14).Equals("musicsearch://")))
      pItem->SetCanQueue(false);
    
    CStdString strIcon;
    // We have the real DVD-ROM, set icon on disktype
    if (share.m_iDriveType == CMediaSource::SOURCE_TYPE_DVD && share.m_strThumbnailImage.IsEmpty())
    {
      CUtil::GetDVDDriveIcon( pItem->GetPath(), strIcon );
      // CDetectDVDMedia::SetNewDVDShareUrl() caches disc thumb as special://temp/dvdicon.tbn
      CStdString strThumb = "special://temp/dvdicon.tbn";
      if (XFILE::CFile::Exists(strThumb))
        pItem->SetThumbnailImage(strThumb);
    }
    else if (pItem->GetPath().Left(9) == "addons://")
      strIcon = "DefaultHardDisk.png";
    else if (pItem->IsLastFM()
             || pItem->IsVideoDb()
             || pItem->IsMusicDb()
             || pItem->IsPlugin()
             || pItem->GetPath() == "special://musicplaylists/"
             || pItem->GetPath() == "special://videoplaylists/"
             || pItem->GetPath() == "musicsearch://")
      strIcon = "DefaultFolder.png";
    else if (pItem->IsRemote())
      strIcon = "DefaultNetwork.png";
    else if (pItem->IsISO9660())
      strIcon = "DefaultDVDRom.png";
    else if (pItem->IsDVD())
      strIcon = "DefaultDVDRom.png";
    else if (pItem->IsCDDA())
      strIcon = "DefaultCDDA.png";
    else if (pItem->IsRemovable() && g_TextureManager.HasTexture("DefaultRemovableDisk.png"))
      strIcon = "DefaultRemovableDisk.png";
    else
      strIcon = "DefaultHardDisk.png";
    
    pItem->SetIconImage(strIcon);
    if (share.m_iHasLock == 2 && g_settings.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE)
      pItem->SetOverlayImage(CGUIListItem::ICON_OVERLAY_LOCKED);
    else
      pItem->SetOverlayImage(CGUIListItem::ICON_OVERLAY_NONE);
    
    items.Add(pItem);
  }
  return true;
}

bool CSourcesDirectory::Exists(const char* strPath)
{
  return true;
}
