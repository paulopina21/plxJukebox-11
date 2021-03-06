


#include "system.h"
#include "Util.h"
#include "utils/URIUtils.h"
#include "FactoryFileDirectory.h"
#ifdef HAS_FILESYSTEM
#include "OGGFileDirectory.h"
#include "NSFFileDirectory.h"
#include "SIDFileDirectory.h"
#include "ASAPFileDirectory.h"
#include "RSSDirectory.h"
#include "cores/paplayer/ASAPCodec.h"
#endif
#ifdef HAS_FILESYSTEM_RAR
#include "RarDirectory.h"
#endif
#include "ZipDirectory.h"
#include "SmartPlaylistDirectory.h"
#include "playlists/SmartPlayList.h"
#include "PlaylistFileDirectory.h"
#include "playlists/PlayListFactory.h"
#include "Directory.h"
#include "File.h"
#include "ZipManager.h"
#include "settings/AdvancedSettings.h"
#include "FileItem.h"
#include "PFCManager.h" // Laureon: Filesystem: Added
#include "PFCDirectory.h" // Laureon: Filesystem: Added

using namespace XFILE;
using namespace PLAYLIST;
using namespace std;

CFactoryFileDirectory::CFactoryFileDirectory(void)
{}

CFactoryFileDirectory::~CFactoryFileDirectory(void)
{}

// return NULL + set pItem->m_bIsFolder to remove it completely from list.
IFileDirectory* CFactoryFileDirectory::Create(const CStdString& strPath, CFileItem* pItem, const CStdString& strMask)
{
  CStdString strExtension=URIUtils::GetExtension(strPath);
  strExtension.MakeLower();

#ifdef HAS_FILESYSTEM
  if ((strExtension.Equals(".ogg") || strExtension.Equals(".oga")) && CFile::Exists(strPath))
  {
    IFileDirectory* pDir=new COGGFileDirectory;
    //  Has the ogg file more than one bitstream?
    if (pDir->ContainsFiles(strPath))
    {
      return pDir; // treat as directory
    }

    delete pDir;
    return NULL;
  }
  if (strExtension.Equals(".nsf") && CFile::Exists(strPath))
  {
    IFileDirectory* pDir=new CNSFFileDirectory;
    //  Has the nsf file more than one track?
    if (pDir->ContainsFiles(strPath))
      return pDir; // treat as directory

    delete pDir;
    return NULL;
  }
  if (strExtension.Equals(".sid") && CFile::Exists(strPath))
  {
    IFileDirectory* pDir=new CSIDFileDirectory;
    //  Has the sid file more than one track?
    if (pDir->ContainsFiles(strPath))
      return pDir; // treat as directory

    delete pDir;
    return NULL;
  }
#ifdef HAS_ASAP_CODEC
  if (ASAPCodec::IsSupportedFormat(strExtension) && CFile::Exists(strPath))
  {
    IFileDirectory* pDir=new CASAPFileDirectory;
    //  Has the asap file more than one track?
    if (pDir->ContainsFiles(strPath))
      return pDir; // treat as directory

    delete pDir;
    return NULL;
  }
#endif

  if (pItem->IsRSS())
    return new CRSSDirectory();

#endif
  if (strExtension.Equals(".zip"))
  {
    CStdString strUrl;
    URIUtils::CreateArchivePath(strUrl, "zip", strPath, "");

    CFileItemList items;
    CDirectory::GetDirectory(strUrl, items, strMask);
    if (items.Size() == 0) // no files
      pItem->m_bIsFolder = true;
    else if (items.Size() == 1 && items[0]->m_idepth == 0)
    {
      // one STORED file - collapse it down
      *pItem = *items[0];
    }
    else
    { // compressed or more than one file -> create a zip dir
      pItem->SetPath(strUrl);
      return new CZipDirectory;
    }
    return NULL;
  }

//	if (strExtension.Equals(".pfc")) // Laureon: Added: Filesystem
//	{
//		CStdString strUrl;
//		URIUtils::CreateArchivePath(strUrl, "pfc", strPath, "");
//
//		pItem->SetPath(strUrl);
//		CURL urlPath(strPath);
//		CStdString strFile = urlPath.GetHostName();

//		int type = g_PFCManager.GetPFCType(strPath);
//		switch (type) {
//			case RPF_PACK_TYPE_ALBUM: {
//				CFileItem item(strPath, g_PFCManager.GetAlbumInfo(strFile));
//				URIUtils::CreateArchivePath(strUrl, "pfc", strFile, "cover.jpg");
//				item.SetMusicThumb();
//				item.SetThumbnailImage(strUrl);
//				*pItem = item;
//
//				return new CPFCDirectory;

//			}
//			case RPF_PACK_TYPE_PACKAGE:
//				return new CPFCDirectory;
//			break;
//			case RPF_PACK_TYPE_NONE:
//				return NULL;
//			break;
//			default:
//				return new CPFCDirectory;
//			break;
//		}
//	}

  if (strExtension.Equals(".rar") || strExtension.Equals(".001"))
  {
    CStdString strUrl;
    URIUtils::CreateArchivePath(strUrl, "rar", strPath, "");

    vector<CStdString> tokens;
    CUtil::Tokenize(strPath,tokens,".");
    if (tokens.size() > 2)
    {
      if (strExtension.Equals(".001"))
      {
        if (tokens[tokens.size()-2].Equals("ts")) // .ts.001 - treat as a movie file to scratch some users itch
          return NULL;
      }
      CStdString token = tokens[tokens.size()-2];
      if (token.Left(4).CompareNoCase("part") == 0) // only list '.part01.rar'
      {
        // need this crap to avoid making mistakes - yeyh for the new rar naming scheme :/
        struct __stat64 stat;
        int digits = token.size()-4;
        CStdString strNumber, strFormat;
        strFormat.Format("part%%0%ii",digits);
        strNumber.Format(strFormat.c_str(),1);
        CStdString strPath2=strPath;
        strPath2.Replace(token,strNumber);
        if (atoi(token.substr(4).c_str()) > 1 && CFile::Stat(strPath2,&stat) == 0)
        {
          pItem->m_bIsFolder = true;
          return NULL;
        }
      }
    }

    CFileItemList items;
    CDirectory::GetDirectory(strUrl, items, strMask);
    if (items.Size() == 0) // no files - hide this
      pItem->m_bIsFolder = true;
    else if (items.Size() == 1 && items[0]->m_idepth == 0x30)
    {
      // one STORED file - collapse it down
      *pItem = *items[0];
    }
    else
    {
#ifdef HAS_FILESYSTEM_RAR
      // compressed or more than one file -> create a rar dir
      pItem->SetPath(strUrl);
      return new CRarDirectory;
#else
      return NULL;
#endif
    }
    return NULL;
  }
  if (strExtension.Equals(".xsp"))
  { // XBMC Smart playlist - just XML renamed to XSP
    // read the name of the playlist in
    CSmartPlaylist playlist;
    if (playlist.OpenAndReadName(strPath))
    {
      pItem->SetLabel(playlist.GetName());
      pItem->SetLabelPreformated(true);
    }
    IFileDirectory* pDir=new CSmartPlaylistDirectory;
    return pDir; // treat as directory
  }
  if (g_advancedSettings.m_playlistAsFolders && CPlayListFactory::IsPlaylist(strPath))
  { // Playlist file
    // currently we only return the directory if it contains
    // more than one file.  Reason is that .pls and .m3u may be used
    // for links to http streams etc.
    IFileDirectory *pDir = new CPlaylistFileDirectory();
    CFileItemList items;
    if (pDir->GetDirectory(strPath, items))
    {
      if (items.Size() > 1)
        return pDir;
    }
    delete pDir;
    return NULL;
  }
  return NULL;
}

