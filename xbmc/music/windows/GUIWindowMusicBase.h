/*!
\file GUIWindowMusicBase.h
\brief
*/

#pragma once



#include "windows/GUIMediaWindow.h"
#include "music/MusicDatabase.h"
#include "video/VideoDatabase.h" // Laureon: Jukebox Music Videos Listing System

#include "music/tags/MusicInfoTagLoaderFactory.h"
#include "music/infoscanner/MusicInfoScraper.h"
#include "PlayListPlayer.h"
#include "music/MusicInfoLoader.h"

#ifdef IS_PROFESSIONAL // Laureon: Added: #include: InsertCoin Dialog
#include "../../dialogs/GUIDialogKaiToast.h"
#endif

/*!
 \ingroup windows
 \brief The base class for music windows

 CGUIWindowMusicBase is the base class for
 all music windows.
 */
class CGUIWindowMusicBase : public CGUIMediaWindow
{
public:
  CGUIWindowMusicBase(int id, const CStdString &xmlFile);
  virtual ~CGUIWindowMusicBase(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnBack(int actionID);

  void OnInfo(CFileItem *pItem, bool bShowInfo = false);
  static void SetupFanart(CFileItemList& items);

protected:
  /*!
  \brief Will be called when an popup context menu has been asked for
  \param itemNumber List/thumb control item that has been clicked on
  */
  virtual void GetContextButtons(int itemNumber, CContextButtons &buttons);
  void GetNonContextButtons(CContextButtons &buttons);
  virtual bool OnContextButton(int itemNumber, CONTEXT_BUTTON button);
  //virtual bool OnContextButton(CFileItemPtr pItem, CONTEXT_BUTTON button); // Laureon: Added: Jukebox Behavior

  /*!
  \brief Overwrite to update your gui buttons (visible, enable,...)
  */
  virtual void UpdateButtons();

  virtual bool GetDirectory(const CStdString &strDirectory, CFileItemList &items);
  virtual void OnRetrieveMusicInfo(CFileItemList& items);
  void AddItemToPlayList(const CFileItemPtr &pItem, CFileItemList &queuedItems);
  virtual void OnScan(int iItem) {};
  void OnRipCD();
  virtual void OnPrepareFileItems(CFileItemList &items);
  virtual CStdString GetStartFolder(const CStdString &dir);

  // new methods
  virtual void PlayItem(int iItem);
  virtual void PlayItem(CFileItemPtr pItem); // Laureon: Added: For Jukebox listing Mode

  virtual bool OnPlayMedia(int iItem);
  virtual bool OnPlayMedia(CFileItemPtr pItem); // Laureon: Added: For Jukebox listing Mode

  void RetrieveMusicInfo();
  void OnInfo(int iItem, bool bShowInfo = true);
  void OnInfoAll(int iItem, bool bCurrent=false);
  virtual void OnQueueItem(int iItem);
  virtual void OnQueueItem(CFileItemPtr pItem); // Laureon Added: For Jukebox listing Mode

  enum ALLOW_SELECTION { SELECTION_ALLOWED = 0, SELECTION_AUTO, SELECTION_FORCED };
  bool FindAlbumInfo(const CStdString& strAlbum, const CStdString& strArtist, MUSIC_GRABBER::CMusicAlbumInfo& album, ALLOW_SELECTION allowSelection);
  bool FindArtistInfo(const CStdString& strArtist, MUSIC_GRABBER::CMusicArtistInfo& artist, ALLOW_SELECTION allowSelection);

  void ShowAlbumInfo(const CAlbum &album, const CStdString &strPath, bool bRefresh, bool bShowInfo = true);
  void ShowArtistInfo(const CArtist &artist, const CStdString &strPath, bool bRefresh, bool bShowInfo = true);
  void ShowSongInfo(CFileItem* pItem);
  void UpdateThumb(const CAlbum &album, const CStdString &path);

  void OnManualAlbumInfo();
  void OnRipTrack(int iItem);
  void OnSearch();
  virtual void LoadPlayList(const CStdString& strPlayList);

  typedef std::vector <CFileItem*>::iterator ivecItems; ///< CFileItem* vector Iterator
  CGUIDialogProgress* m_dlgProgress; ///< Progress dialog
#ifdef IS_PROFESSIONAL // Laureon: Added: InsertCoin Dialog
  CGUIDialogKaiToast *m_dlgInsertCoin; 
#endif

  // member variables to save frequently used g_guiSettings (which is slow)
  bool m_hideExtensions;
  CMusicDatabase m_musicdatabase;
  CVideoDatabase m_videodatabase; // Laureon: Added: Jukebox Music Videos listing system

  MUSIC_INFO::CMusicInfoLoader m_musicInfoLoader;
};
