#pragma once



#include "guilib/GUIDialog.h"
#include "guilib/GUIListItem.h"
#include "ThumbLoader.h"
#include "video/VideoDatabase.h"

class CFileItem;

class CGUIDialogVideoInfo :
      public CGUIDialog
{
public:
  CGUIDialogVideoInfo(void);
  virtual ~CGUIDialogVideoInfo(void);
  virtual bool OnMessage(CGUIMessage& message);
  void SetMovie(const CFileItem *item);
  bool NeedRefresh() const;
  bool RefreshAll() const;
  bool HasUpdatedThumb() const { return m_hasUpdatedThumb; };

  const CStdString &GetThumbnail() const;
  virtual CFileItemPtr GetCurrentListItem(int offset = 0) { return m_movieItem; }
  const CFileItemList& CurrentDirectory() const { return *m_castList; };
  virtual bool HasListItems() const { return true; };
protected:
  void Refresh();
  void Update();
  void SetLabel(int iControl, const CStdString& strLabel);

  // link cast to movies
  void ClearCastList();
  void OnSearch(CStdString& strSearch);
  void DoSearch(CStdString& strSearch, CFileItemList& items);
  void OnSearchItemFound(const CFileItem* pItem);
  void Play(bool resume = false);
  void OnGetThumb();
  void OnGetFanart();
  void PlayTrailer();

  CFileItemPtr m_movieItem;
  CFileItemList *m_castList;
  bool m_bViewReview;
  bool m_bRefresh;
  bool m_bRefreshAll;
  bool m_hasUpdatedThumb;
  CGUIDialogProgress* m_dlgProgress;
  CVideoThumbLoader m_loader;
};
