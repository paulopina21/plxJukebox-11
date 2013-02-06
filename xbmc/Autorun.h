#pragma once



//  CAutorun   -  Autorun for different Cd Media
//         like DVD Movies or XBOX Games
//
// by Bobbin007 in 2003
//
//
//

#include "system.h" // for HAS_DVD_DRIVE

#ifdef HAS_DVD_DRIVE

#include "utils/StdString.h"

namespace XFILE
{
  class IDirectory;
}

namespace MEDIA_DETECT
{
class CAutorun
{
public:
  CAutorun();
  virtual ~CAutorun();
  static bool CanResumePlayDVD(const CStdString& path);
  static bool PlayDisc(const CStdString& path="", bool bypassSettings = false, bool startFromBeginning = false);
  static bool PlayDiscAskResume(const CStdString& path="");
  bool IsEnabled() const;
  void Enable();
  void Disable();
  void HandleAutorun();
  static void ExecuteAutorun(const CStdString& path = "", bool bypassSettings = false, bool ignoreplaying = false, bool startFromBeginning = false);
protected:
  static bool RunDisc(XFILE::IDirectory* pDir, const CStdString& strDrive, int& nAddedToPlaylist, bool bRoot, bool bypassSettings, bool startFromBeginning);
  bool m_bEnable;
};
}

#endif
