#pragma once



#include "guilib/GUIDialog.h"
#include "music/Song.h"
#include "music/Artist.h"
#include "music/Album.h"

class CFileItem;
class CFileItemList;

class CGUIDialogMusicInfo :
      public CGUIDialog
{
public:
  CGUIDialogMusicInfo(void);
  virtual ~CGUIDialogMusicInfo(void);
  virtual bool OnMessage(CGUIMessage& message);
  void SetAlbum(const CAlbum& album, const CStdString &path);
  void SetArtist(const CArtist& artist, const CStdString &path);
  bool NeedRefresh() const;
  bool HasUpdatedThumb() const { return m_hasUpdatedThumb; };
  void RefreshThumb();

  virtual bool HasListItems() const { return true; };
  virtual CFileItemPtr GetCurrentListItem(int offset = 0);
  const CFileItemList& CurrentDirectory() const { return *m_albumSongs; };
protected:
  virtual void OnInitWindow();
  void Update();
  void SetLabel(int iControl, const CStdString& strLabel);
  bool DownloadThumbnail(const CStdString &thumbFile);
  void OnGetThumb();
  void OnGetFanart();
  void SetSongs(const VECSONGS &songs);
  void SetDiscography();
  void OnSearch(const CFileItem* pItem);

  CAlbum m_album;
  CArtist m_artist;
  bool m_bViewReview;
  bool m_bRefresh;
  bool m_hasUpdatedThumb;
  bool m_bArtistInfo;
  CFileItemPtr   m_albumItem;
  CFileItemList* m_albumSongs;
};
