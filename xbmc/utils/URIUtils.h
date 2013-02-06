
#pragma once

#include "StdString.h"

class CURL;

class URIUtils
{
public:
  URIUtils(void);
  virtual ~URIUtils(void);
  static CStdString GetParentFolderURI(const CStdString& uri,
                                       bool preserveFileNameInPath);
  static bool IsInPath(const CStdString &uri, const CStdString &baseURI);

  static void GetDirectory(const CStdString& strFilePath,
                           CStdString& strDirectoryPath);
  static const CStdString GetExtension(const CStdString& strFileName);
  static void GetExtension(const CStdString& strFile, CStdString& strExtension);
  static const CStdString GetFileName(const CStdString& strFileNameAndPath);
  static void RemoveExtension(CStdString& strFileName);
  static CStdString ReplaceExtension(const CStdString& strFile,
                                     const CStdString& strNewExtension);
  static void Split(const CStdString& strFileNameAndPath, 
                    CStdString& strPath, CStdString& strFileName);
  static CStdStringArray SplitPath(const CStdString& strPath);

  static void GetCommonPath(CStdString& strPath, const CStdString& strPath2);
  static CStdString GetParentPath(const CStdString& strPath);
  static bool GetParentPath(const CStdString& strPath, CStdString& strParent);
  static CStdString SubstitutePath(const CStdString& strPath);

  static bool IsAddonsPath(const CStdString& strFile);
  static bool IsSourcesPath(const CStdString& strFile);
  static bool IsCDDA(const CStdString& strFile);
  static bool IsDAAP(const CStdString& strFile);
  static bool IsDOSPath(const CStdString &path);
  static bool IsDVD(const CStdString& strFile);
  static bool IsFTP(const CStdString& strFile);
  static bool IsHD(const CStdString& strFileName);
  static bool IsHDHomeRun(const CStdString& strFile);
  static bool IsSlingbox(const CStdString& strFile);
  static bool IsHTSP(const CStdString& strFile);
  static bool IsInArchive(const CStdString& strFile);
  static bool IsInPFC(const CStdString& strFile); // Laureon: Added: PFC Filesystem
  static bool IsInRAR(const CStdString& strFile);
  static bool IsInternetStream(const CURL& url, bool bStrictCheck = false);
  static bool IsInZIP(const CStdString& strFile);
  static bool IsISO9660(const CStdString& strFile);
  static bool IsLastFM(const CStdString& strFile);
  static bool IsLiveTV(const CStdString& strFile);
  static bool IsMultiPath(const CStdString& strPath);
  static bool IsMusicDb(const CStdString& strFile);
  static bool IsMythTV(const CStdString& strFile);
  static bool IsNfs(const CStdString& strFile);  
  static bool IsAfp(const CStdString& strFile);    
  static bool IsOnDVD(const CStdString& strFile);
  static bool IsOnLAN(const CStdString& strFile);
  static bool IsPlugin(const CStdString& strFile);
  static bool IsScript(const CStdString& strFile);
  static bool IsPFC(const CStdString& strFile); // Laureon: Added: PFC Filesystem
  static bool IsRAR(const CStdString& strFile);
  static bool IsRemote(const CStdString& strFile);
  static bool IsSmb(const CStdString& strFile);
  static bool IsSpecial(const CStdString& strFile);
  static bool IsStack(const CStdString& strFile);
  static bool IsTuxBox(const CStdString& strFile);
  static bool IsUPnP(const CStdString& strFile);
  static bool IsURL(const CStdString& strFile);
  static bool IsVideoDb(const CStdString& strFile);
  static bool IsVTP(const CStdString& strFile);
  static bool IsZIP(const CStdString& strFile);

  static void AddSlashAtEnd(CStdString& strFolder);
  static bool HasSlashAtEnd(const CStdString& strFile);
  static void RemoveSlashAtEnd(CStdString& strFolder);

  static void CreateArchivePath(CStdString& strUrlPath,
                                const CStdString& strType,
                                const CStdString& strArchivePath,
                                const CStdString& strFilePathInArchive,
                                const CStdString& strPwd="");

  static void AddFileToFolder(const CStdString& strFolder,
                              const CStdString& strFile, CStdString& strResult);
  static CStdString AddFileToFolder(const CStdString &strFolder, 
                                    const CStdString &strFile)
  {
    CStdString result;
    AddFileToFolder(strFolder, strFile, result);
    return result;
  }

  static bool ProtocolHasParentInHostname(const CStdString& prot);
  static bool ProtocolHasEncodedHostname(const CStdString& prot);
};

