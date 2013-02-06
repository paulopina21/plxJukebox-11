#pragma once


#include <map>
#include "utils/StdString.h"

// static class for path translation from our special:// URLs.

/* paths are as follows:

 special://root/          - the main XBMC folder (i.e. where the app resides).
 special://home/          - a writeable version of the main XBMC folder
                             Linux: ~/.xbmc/
                             OS X:  ~/Library/Application Support/XBMC/
                             Win32: ~/Application Data/XBMC/
 special://userhome/      - a writable version of the user home directory
                             Linux, OS X: ~/.xbmc
                             Win32: home directory of user
 special://masterprofile/ - the master users userdata folder - usually special://home/userdata
                             Linux: ~/.xbmc/userdata/
                             OS X:  ~/Library/Application Support/XBMC/UserData/
                             Win32: ~/Application Data/XBMC/UserData/
 special://profile/       - the current users userdata folder - usually special://masterprofile/profiles/<current_profile>
                             Linux: ~/.xbmc/userdata/profiles/<current_profile>
                             OS X:  ~/Library/Application Support/XBMC/UserData/profiles/<current_profile>
                             Win32: ~/Application Data/XBMC/UserData/profiles/<current_profile>

 special://temp/          - the temporary directory.
                             Linux: ~/tmp/xbmc<username>
                             OS X:  ~/
                             Win32: ~/Application Data/XBMC/cache
*/
class CURL;
class CSpecialProtocol
{
public:
  static void SetProfilePath(const CStdString &path);
  static void SetXBMCPath(const CStdString &path);
  static void SetXBMCBinPath(const CStdString &path);
  static void SetXBMCFrameworksPath(const CStdString &path);
  static void SetHomePath(const CStdString &path);
  static void SetUserHomePath(const CStdString &path);
  static void SetMasterProfilePath(const CStdString &path);
  static void SetTempPath(const CStdString &path);

  static bool ComparePath(const CStdString &path1, const CStdString &path2);
  static void LogPaths();

  static CStdString TranslatePath(const CStdString &path);
  static CStdString TranslatePath(const CURL &url);
  static CStdString TranslatePathConvertCase(const CStdString& path);

private:
  static void SetPath(const CStdString &key, const CStdString &path);
  static CStdString GetPath(const CStdString &key);

  static std::map<CStdString, CStdString> m_pathMap;
};

#define _P(x)     CSpecialProtocol::TranslatePath(x)
#define PTH_IC(x) CSpecialProtocol::TranslatePathConvertCase(x)

#ifdef _WIN32
#define PATH_SEPARATOR_CHAR '\\'
#define PATH_SEPARATOR_STRING "\\"
#else
#define PATH_SEPARATOR_CHAR '/'
#define PATH_SEPARATOR_STRING "/"
#endif
