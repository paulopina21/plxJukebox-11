#pragma once



#include "windows/GUIMediaWindow.h"
#include "GUIWindowSlideShow.h"
#include "PictureThumbLoader.h"
#include "DllImageLib.h"

class CGUIDialogProgress;

class CGUIWindowPictures : public CGUIMediaWindow, public IBackgroundLoaderObserver
{
public:
  CGUIWindowPictures(void);
  virtual ~CGUIWindowPictures(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual void OnInitWindow();

protected:
  virtual bool GetDirectory(const CStdString &strDirectory, CFileItemList& items);
  virtual void OnInfo(int item);
  virtual bool OnClick(int iItem);
  virtual void UpdateButtons();
  virtual void OnPrepareFileItems(CFileItemList& items);
  virtual bool Update(const CStdString &strDirectory);
  virtual void GetContextButtons(int itemNumber, CContextButtons &buttons);
  virtual bool OnContextButton(int itemNumber, CONTEXT_BUTTON button);
  virtual CStdString GetStartFolder(const CStdString &dir);

  void OnRegenerateThumbs();
  virtual bool OnPlayMedia(int iItem);
  bool ShowPicture(int iItem, bool startSlideShow);
  void OnShowPictureRecursive(const CStdString& strPath);
  void OnSlideShow(const CStdString& strPicture);
  void OnSlideShow();
  void OnSlideShowRecursive(const CStdString& strPicture);
  void OnSlideShowRecursive();
  virtual void OnItemLoaded(CFileItem* pItem);
  virtual void LoadPlayList(const CStdString& strPlayList);

  CGUIDialogProgress* m_dlgProgress;
  DllImageLib m_ImageLib;

  CPictureThumbLoader m_thumbLoader;
  bool m_slideShowStarted;
};
