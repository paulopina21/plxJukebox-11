#pragma once



#include "filesystem/File.h"
#include "threads/Thread.h"
#include "threads/SystemClock.h"

class CGUIDialogProgress;

class CGUIDialogCache : public CThread, public XFILE::IFileCallback
{
public:
  CGUIDialogCache(DWORD dwDelay = 0, const CStdString& strHeader="", const CStdString& strMsg="");
  virtual ~CGUIDialogCache();
  void SetHeader(const CStdString& strHeader);
  void SetHeader(int nHeader);
  void SetMessage(const CStdString& strMessage);
  bool IsCanceled() const;
  void ShowProgressBar(bool bOnOff);
  void SetPercentage(int iPercentage);

  void Close(bool bForceClose = false);

  virtual void Process();
  virtual bool OnFileCallback(void* pContext, int ipercent, float avgSpeed);

protected:

  void OpenDialog();

  XbmcThreads::EndTime m_endtime;
  CGUIDialogProgress* m_pDlg;
  CStdString m_strLinePrev;
  CStdString m_strLinePrev2;
  CStdString m_strHeader;
  bool bSentCancel;
  bool m_bOpenTried;
};
