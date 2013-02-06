#pragma once



#include "GUIWindowVideoBase.h"
#include "ThumbLoader.h"

class CFileItemList;

class CGUIWindowVideoNav : public CGUIWindowVideoBase
{
public:

  CGUIWindowVideoNav(void);
  virtual ~CGUIWindowVideoNav(void);

  virtual bool OnAction(const CAction &action);
  virtual bool OnMessage(CGUIMessage& message);

  virtual void OnPrepareFileItems(CFileItemList &items);
  virtual void OnInfo(CFileItem* pItem, ADDON::ScraperPtr &info);
  static bool CanDelete(const CStdString& strPath);
  static bool DeleteItem(CFileItem* pItem, bool bUnavailable=false);

protected:
  /*! \brief Load video information from the database for these items
   Useful for grabbing information for file listings, from watched status to full metadata
   \param items the items to load information for.
   */
  void LoadVideoInfo(CFileItemList &items);

  virtual void OnItemLoaded(CFileItem* pItem);
  void OnLinkMovieToTvShow(int itemnumber, bool bRemove);
  // override base class methods
  virtual bool GetDirectory(const CStdString &strDirectory, CFileItemList &items);
  virtual void UpdateButtons();
  virtual void DoSearch(const CStdString& strSearch, CFileItemList& items);
  virtual void PlayItem(int iItem);
  virtual void OnDeleteItem(CFileItemPtr pItem);
  virtual void GetContextButtons(int itemNumber, CContextButtons &buttons);
  virtual bool OnContextButton(int itemNumber, CONTEXT_BUTTON button);
  virtual bool OnClick(int iItem);
  virtual CStdString GetStartFolder(const CStdString &dir);

  virtual CStdString GetQuickpathName(const CStdString& strPath) const;

  VECSOURCES m_shares;
};
