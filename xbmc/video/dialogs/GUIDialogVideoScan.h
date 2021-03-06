#pragma once



#include "guilib/GUIDialog.h"
#include "video/VideoInfoScanner.h"
#include "threads/CriticalSection.h"

class CGUIDialogVideoScan: public CGUIDialog, public VIDEO::IVideoInfoScannerObserver
{
public:
  CGUIDialogVideoScan(void);
  virtual ~CGUIDialogVideoScan(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual void FrameMove();

  void StartScanning(const CStdString& strDirectory, bool scanAll = false);
  bool IsScanning();
  void StopScanning();

  void UpdateState();
protected:
  int GetStateString();
  virtual void OnDirectoryChanged(const CStdString& strDirectory);
  virtual void OnDirectoryScanned(const CStdString& strDirectory);
  virtual void OnFinished();
  virtual void OnStateChanged(VIDEO::SCAN_STATE state);
  virtual void OnSetProgress(int currentItem, int itemCount);
  virtual void OnSetCurrentProgress(int currentItem, int itemCount);
  virtual void OnSetTitle(const CStdString& strTitle);

  VIDEO::CVideoInfoScanner m_videoInfoScanner;
  VIDEO::SCAN_STATE m_ScanState;
  CStdString m_strCurrentDir;
  CStdString m_strTitle;

  CCriticalSection m_critical;

  float m_fPercentDone;
  float m_fCurrentPercentDone;
  int m_currentItem;
  int m_itemCount;
};
