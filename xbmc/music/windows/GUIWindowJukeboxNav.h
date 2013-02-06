#pragma once

#include "GUIWindowJukeboxBase.h"
#include "ThumbLoader.h"
#include "utils/Stopwatch.h"

class CFileItemList;

class CGUIWindowJukeboxNav : public CGUIWindowJukeboxBase, public IBackgroundLoaderObserver
{
public:

  CGUIWindowJukeboxNav(void);
  virtual ~CGUIWindowJukeboxNav(void);

  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction& action);
  virtual void FrameMove();

  virtual void OnPrepareFileItems(CFileItemList &items);
protected:
  virtual void OnItemLoaded(CFileItem* pItem) {};
  // override base class methods
  virtual bool GetDirectory(const CStdString &strDirectory, CFileItemList &items);
  virtual void UpdateButtons();
  virtual void PlayItem(CFileItemPtr pItem);
  virtual void OnWindowLoaded();
  virtual void GetContextButtons(CFileItemPtr pItem, CContextButtons &buttons);
  virtual bool OnContextButton(CFileItemPtr pItem, CONTEXT_BUTTON button);
  virtual bool OnClick(CFileItemPtr pItem); // Laureon: Added: Jukebox Listing System
  virtual CStdString GetStartFolder(const CStdString &url);

  bool GetSongsFromAlbum(CFileItemPtr pItem, CFileItemList &items);
  void UpdateSongsControl();
  
  bool GetSongsFromPlayList(const CStdString& strPlayList, CFileItemList &items);
  void DisplayEmptyDatabaseMessage(bool bDisplay);
  CStdString GetQuickpathName(const CStdString& strPath) const;

  VECSOURCES m_shares;

  bool m_bDisplayEmptyDatabaseMessage;  ///< If true we display a message informing the user to switch back to the Files view.

  CMusicThumbLoader m_thumbLoader;      ///< used for the loading of thumbs in the special://musicplaylist folder
  //CGUIControl 
//  std::vector<CAnimation> m_animsBackup;
  
  // searching
  void OnSearchUpdate();
  void AddSearchFolder();
  CStopWatch m_searchTimer; ///< Timer to delay a search while more characters are entered
  bool m_searchWithEdit;    ///< Whether the skin supports the new edit control searching
};
