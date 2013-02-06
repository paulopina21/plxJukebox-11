#pragma once



#include "URL.h"
#include "settings/GUISettings.h"
#if _MSC_VER > 1400
#include "Cfgmgr32.h"
#endif
#include "MediaSource.h"
#include "utils/Stopwatch.h"
#include "guilib/Geometry.h"

enum Drive_Types
{
  ALL_DRIVES = 0,
  LOCAL_DRIVES,
  REMOVABLE_DRIVES,
  DVD_DRIVES
};


class CWIN32Util
{
public:
  CWIN32Util(void);
  virtual ~CWIN32Util(void);

  static CStdString URLEncode(const CURL &url);
  static CStdString GetLocalPath(const CStdString &strPath);
  static char FirstDriveFromMask (ULONG unitmask);
  static int GetDriveStatus(const CStdString &strPath);
  static bool PowerManagement(PowerState State);
  static int BatteryLevel();
  static bool XBMCShellExecute(const CStdString &strPath, bool bWaitForScriptExit=false);
  static std::vector<CStdString> GetDiskUsage();
  static CStdString GetResInfoString();
  static int GetDesktopColorDepth();
  static CStdString GetSpecialFolder(int csidl);
  static CStdString CWIN32Util::GetSystemPath();
  static CStdString GetProfilePath();
  static CStdString UncToSmb(const CStdString &strPath);
  static void ExtendDllPath();
  static HRESULT ToggleTray(const char cDriveLetter='\0');
  static HRESULT EjectTray(const char cDriveLetter='\0');
  static HRESULT CloseTray(const char cDriveLetter='\0');
  static bool EjectDrive(const char cDriveLetter='\0');
#ifdef HAS_GL
  static void CheckGLVersion();
  static bool HasGLDefaultDrivers();
  static bool HasReqGLVersion();
#endif
  static BOOL IsCurrentUserLocalAdministrator();
  static void GetDrivesByType(VECSOURCES &localDrives, Drive_Types eDriveType=ALL_DRIVES, bool bonlywithmedia=false);
  static bool IsAudioCD(const CStdString& strPath);
  static CStdString GetDiskLabel(const CStdString& strPath);

  static bool Is64Bit();
  static LONG UtilRegGetValue( const HKEY hKey, const char *const pcKey, DWORD *const pdwType, char **const ppcBuffer, DWORD *const pdwSizeBuff, const DWORD dwSizeAdd );
  static bool UtilRegOpenKeyEx( const HKEY hKeyParent, const char *const pcKey, const REGSAM rsAccessRights, HKEY *hKey, const bool bReadX64= false );

  static bool GetCrystalHDLibraryPath(CStdString &strPath);
  
  static bool GetFocussedProcess(CStdString &strProcessFile);
  static void CropSource(CRect& src, CRect& dst, CRect target);

  static bool IsUsbDevice(const CStdStringW &strWdrive);

private:
#if _MSC_VER > 1400
  static DEVINST GetDrivesDevInstByDiskNumber(long DiskNumber);
#endif
};


class CWinIdleTimer : public CStopWatch
{
public:
  void StartZero();
};
