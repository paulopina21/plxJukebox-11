

#if (defined HAVE_CONFIG_H) && (!defined WIN32)
  #include "config.h"
#endif
#include "system.h"
#include "FactoryDirectory.h"
#include "HDDirectory.h"
#include "SpecialProtocolDirectory.h"
#include "MultiPathDirectory.h"
#include "StackDirectory.h"
#include "FactoryFileDirectory.h"
#include "PlaylistDirectory.h"
#include "MusicDatabaseDirectory.h"
#include "MusicSearchDirectory.h"
#include "VideoDatabaseDirectory.h"
#include "AddonsDirectory.h"
#include "SourcesDirectory.h"
#include "LastFMDirectory.h"
#include "FTPDirectory.h"
#include "HTTPDirectory.h"
#include "DAVDirectory.h"
#include "UDFDirectory.h"
#include "Application.h"
#include "addons/Addon.h"
#include "utils/log.h"

#ifdef HAS_FILESYSTEM_SMB
#ifdef _WIN32
#include "WINSMBDirectory.h"
#else
#include "SMBDirectory.h"
#endif
#endif
#ifdef HAS_FILESYSTEM_CDDA
#include "CDDADirectory.h"
#endif
#include "PluginDirectory.h"
#ifdef HAS_FILESYSTEM
#include "ISO9660Directory.h"
#ifdef HAS_FILESYSTEM_RTV
#include "RTVDirectory.h"
#endif
#ifdef HAS_FILESYSTEM_DAAP
#include "DAAPDirectory.h"
#endif
#endif
#ifdef HAS_UPNP
#include "UPnPDirectory.h"
#endif
#ifdef HAS_FILESYSTEM_SAP
#include "SAPDirectory.h"
#endif
#ifdef HAS_FILESYSTEM_VTP
#include "VTPDirectory.h"
#endif
#ifdef HAS_FILESYSTEM_HTSP
#include "HTSPDirectory.h"
#endif
#include "ZipDirectory.h"
#ifdef HAS_FILESYSTEM_RAR
#include "RarDirectory.h"
#endif
#include "DirectoryTuxBox.h"
#include "HDHomeRun.h"
#include "Slingbox.h"
#include "MythDirectory.h"
#include "FileItem.h"
#include "URL.h"
#include "RSSDirectory.h"
#ifdef HAS_ZEROCONF
#include "ZeroconfDirectory.h"
#endif
#ifdef HAS_FILESYSTEM_SFTP
#include "SFTPDirectory.h"
#endif
#ifdef HAS_FILESYSTEM_NFS
#include "NFSDirectory.h"
#endif
#ifdef HAS_FILESYSTEM_AFP
#include "AFPDirectory.h"
#endif

#include "PFCDirectory.h" // Laureon: Added: Filesystem

using namespace XFILE;

/*!
 \brief Create a IDirectory object of the share type specified in \e strPath .
 \param strPath Specifies the share type to access, can be a share or share with path.
 \return IDirectory object to access the directories on the share.
 \sa IDirectory
 */
IDirectory* CFactoryDirectory::Create(const CStdString& strPath)
{
  CURL url(strPath);

  CFileItem item(strPath, false);
  IFileDirectory* pDir=CFactoryFileDirectory::Create(strPath, &item);
  if (pDir)
    return pDir;

  CStdString strProtocol = url.GetProtocol();

  if (strProtocol.size() == 0 || strProtocol == "file") return new CHDDirectory();
  if (strProtocol == "special") return new CSpecialProtocolDirectory();
  if (strProtocol == "sources") return new CSourcesDirectory();
  if (strProtocol == "addons") return new CAddonsDirectory();
#if defined(HAS_FILESYSTEM_CDDA) && defined(HAS_DVD_DRIVE)
  if (strProtocol == "cdda") return new CCDDADirectory();
#endif
#ifdef HAS_FILESYSTEM
  if (strProtocol == "iso9660") return new CISO9660Directory();
#endif
  if (strProtocol == "udf") return new CUDFDirectory();
  if (strProtocol == "plugin") return new CPluginDirectory();
  if (strProtocol == "pfc") return new CPFCDirectory(); // Laureon: Added: Filesystem
  if (strProtocol == "zip") return new CZipDirectory();
#ifdef HAS_FILESYSTEM_RAR
  if (strProtocol == "rar") return new CRarDirectory();
#endif
  if (strProtocol == "multipath") return new CMultiPathDirectory();
  if (strProtocol == "stack") return new CStackDirectory();
  if (strProtocol == "playlistmusic") return new CPlaylistDirectory();
  if (strProtocol == "playlistvideo") return new CPlaylistDirectory();
  if (strProtocol == "musicdb") return new CMusicDatabaseDirectory();
  if (strProtocol == "musicsearch") return new CMusicSearchDirectory();
  if (strProtocol == "videodb") return new CVideoDatabaseDirectory();
  if (strProtocol == "filereader")
    return CFactoryDirectory::Create(url.GetFileName());

  if( g_application.getNetwork().IsAvailable(true) )  // true to wait for the network (if possible)
  {
    if (strProtocol == "lastfm") return new CLastFMDirectory();
    if (strProtocol == "tuxbox") return new CDirectoryTuxBox();
    if (strProtocol == "ftp" ||  strProtocol == "ftpx" ||  strProtocol == "ftps") return new CFTPDirectory();
    if (strProtocol == "http" || strProtocol == "https") return new CHTTPDirectory();
    if (strProtocol == "dav" || strProtocol == "davs") return new CDAVDirectory();
#ifdef HAS_FILESYSTEM_SFTP
    if (strProtocol == "sftp" || strProtocol == "ssh") return new CSFTPDirectory();
#endif
#ifdef HAS_FILESYSTEM_SMB
#ifdef _WIN32
    if (strProtocol == "smb") return new CWINSMBDirectory();
#else
    if (strProtocol == "smb") return new CSMBDirectory();
#endif
#endif
#ifdef HAS_FILESYSTEM
#ifdef HAS_FILESYSTEM_DAAP
    if (strProtocol == "daap") return new CDAAPDirectory();
#endif
#ifdef HAS_FILESYSTEM_RTV
    if (strProtocol == "rtv") return new CRTVDirectory();
#endif
#endif
#ifdef HAS_UPNP
    if (strProtocol == "upnp") return new CUPnPDirectory();
#endif
    if (strProtocol == "hdhomerun") return new CDirectoryHomeRun();
    if (strProtocol == "sling") return new CSlingboxDirectory();
    if (strProtocol == "myth") return new CMythDirectory();
    if (strProtocol == "cmyth") return new CMythDirectory();
    if (strProtocol == "rss") return new CRSSDirectory();
#ifdef HAS_FILESYSTEM_SAP
    if (strProtocol == "sap") return new CSAPDirectory();
#endif
#ifdef HAS_FILESYSTEM_VTP
    if (strProtocol == "vtp") return new CVTPDirectory();
#endif
#ifdef HAS_FILESYSTEM_HTSP
    if (strProtocol == "htsp") return new CHTSPDirectory();
#endif
#ifdef HAS_ZEROCONF
    if (strProtocol == "zeroconf") return new CZeroconfDirectory();
#endif
#ifdef HAS_FILESYSTEM_NFS
    if (strProtocol == "nfs") return new CNFSDirectory();
#endif
#ifdef HAS_FILESYSTEM_AFP
      if (strProtocol == "afp") return new CAFPDirectory();
#endif
  }

  CLog::Log(LOGWARNING, "%s - Unsupported protocol(%s) in %s", __FUNCTION__, strProtocol.c_str(), url.Get().c_str() );
  return NULL;
}

