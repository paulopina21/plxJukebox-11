#pragma once



#include "GUIDialogSettings.h"
#include "GUIPassword.h"
#include "Profile.h"

class CGUIDialogLockSettings : public CGUIDialogSettings
{
public:
  CGUIDialogLockSettings(void);
  virtual ~CGUIDialogLockSettings(void);
  static bool ShowAndGetLock(LockType& iLockMode, CStdString& strPassword, int iHeader=20091);
  static bool ShowAndGetLock(CProfile::CLock &locks, int iButtonLabel = 20091, bool bConditional = false, bool bDetails = true);
  static bool ShowAndGetUserAndPassword(CStdString& strUser, CStdString& strPassword, const CStdString& strURL, bool *saveUserDetails);
protected:
  virtual void OnCancel();
  virtual void SetupPage();
  virtual void CreateSettings();
  virtual void OnSettingChanged(SettingInfo &setting);
  void EnableDetails(bool bEnable);

  CProfile::CLock m_locks;
  CStdString m_strUser;
  CStdString m_strURL;
  bool m_bChanged;
  bool m_bDetails;
  bool m_bConditionalDetails;
  bool m_bGetUser;
  int m_iButtonLabel;
  bool *m_saveUserDetails;
};


