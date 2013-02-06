#pragma once

#include "GUIWindowJukeboxBase.h"
#include "ThumbLoader.h"

class CGUIWindowJukeboxSongs : public CGUIWindowJukeboxBase, public IBackgroundLoaderObserver
{
public:
  CGUIWindowJukeboxSongs(void);
  virtual ~CGUIWindowJukeboxSongs(void);

  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction& action);

  void DoScan(const CStdString &strPath);
protected:
  virtual void OnItemLoaded(CFileItem* pItem) {};
  virtual bool GetDirectory(const CStdString &strDirectory, CFileItemList &items);
  virtual void UpdateButtons();
  virtual bool Update(const CStdString &strDirectory);
  virtual void OnPrepareFileItems(CFileItemList &items);
  virtual void GetContextButtons(CFileItemPtr pItem, CContextButtons &buttons);
  virtual bool OnContextButton(CFileItemPtr pItem, CONTEXT_BUTTON button);
  virtual void OnScan(CFileItemPtr pItem);
  virtual void OnRemoveSource(CFileItemPtr pItem);
  virtual CStdString GetStartFolder(const CStdString &dir);

  // new method
  virtual void PlayItem(CFileItemPtr pItem);

  void DeleteRemoveableMediaDirectoryCache();

  CMusicThumbLoader m_thumbLoader;
};
