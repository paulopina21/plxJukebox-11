#pragma once

#include "guilib/GUIWindow.h"
#include "filesystem/VirtualDirectory.h"
#include "filesystem/DirectoryHistory.h"
#include "GUIViewControl.h"
#include "dialogs/GUIDialogContextMenu.h"

class CFileItemList;

// base class for all media windows
class CGUIJukeboxWindow : public CGUIWindow
{
public:
  CGUIJukeboxWindow(int id, const char *xmlFile);
  virtual ~CGUIJukeboxWindow(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
  virtual bool OnBack(int actionID);
  virtual void OnWindowLoaded();
  virtual void OnWindowUnload();
  virtual void OnInitWindow();
  virtual bool IsMediaWindow() const { return true; };
  const CFileItemList &CurrentDirectory() const;
  int GetViewContainerID() const { return m_albunsViewControl.GetCurrentControl(); };
  virtual bool HasListItems() const { return true; };
  virtual CFileItemPtr GetCurrentListItem(int offset = 0);
  const CGUIViewState *GetViewState() const;

protected:
  virtual void LoadAdditionalTags(TiXmlElement *root);
  CGUIControl *GetFirstFocusableControl(int id);
  //virtual void SetupShares();
  virtual void GoParentFolder();
  virtual bool OnClick(CFileItemPtr pItem); // Laureon: Added: For Jukebox Mode

  /* \brief React to a "Select" action on an item in a view.
   \param item selected item.
   \return true if the action is handled, false otherwise.
   */
  virtual bool OnSelect(CFileItemPtr pItem); // Laureon: Added: For Jukebox Mode
  virtual bool OnPopupMenu(CFileItemPtr pItem);
  virtual void GetContextButtons(CFileItemPtr pItem, CContextButtons &buttons);
  virtual bool OnContextButton(CFileItemPtr pItem, CONTEXT_BUTTON button);
  virtual void FormatItemLabels(CFileItemList &items, const LABEL_MASKS &labelMasks);
  virtual void UpdateButtons();
  virtual bool GetDirectory(const CStdString &strDirectory, CFileItemList &items);
  virtual bool Update(const CStdString &strDirectory);
  virtual void FormatAndSort(CFileItemList &items);
  virtual void OnPrepareFileItems(CFileItemList &items);
  virtual void OnFinalizeFileItems(CFileItemList &items);

  void ClearFileItems();
  virtual void SortItems(CFileItemList &items);

  /* \brief Called on response to a GUI_MSG_FILTER_ITEMS message
   Filters the current list with the given filter using FilterItems()
   \param filter the filter to use.
   \sa FilterItems
   */
  void OnFilterItems(const CStdString &filter);

  /* \brief Retrieve the filtered item list
   \param filter filter to apply
   \param items CFileItemList to filter
   \sa OnFilterItems
   */
  void GetFilteredItems(const CStdString &filter, CFileItemList &items);

  // check for a disc or connection
  virtual bool HaveDiscOrConnection(const CStdString& strPath, int iDriveType);
  void ShowShareErrorMessage(CFileItem* pItem);

  void GetDirectoryHistoryString(const CFileItem* pItem, CStdString& strHistoryString);
  void SetHistoryForPath(const CStdString& strDirectory);
  virtual void LoadPlayList(const CStdString& strFileName) {}
  virtual bool OnPlayMedia(CFileItemPtr pItem); // Laureon: Added: For Jukebox Mode
  virtual bool OnPlayAndQueueMedia(const CFileItemPtr &item);
  void UpdateFileList();
  virtual void OnDeleteItem(CFileItemPtr pItem);
  void OnRenameItem(CFileItemPtr pItem);

protected:
  bool WaitForNetwork() const;

  /*! \brief Translate the folder to start in from the given quick path
   \param dir the folder the user wants
   \return the resulting path */
  virtual CStdString GetStartFolder(const CStdString &url);

  XFILE::CVirtualDirectory m_rootDir;

  CGUIViewControl m_albunsViewControl;
  CGUIViewControl m_tracksViewControl;
  CGUIViewControl m_playlistViewControl;

  // current path and history
  CFileItemList* m_vecItems;
  CFileItemList* m_vecTracks; 
  CFileItemList* m_vecPlaylist;

  CFileItemList* m_unfilteredItems;        ///< \brief items prior to filtering using FilterItems()
  CDirectoryHistory m_history;
  std::auto_ptr<CGUIViewState> m_guiState;

  // save control state on window exit
  int m_iLastControl;
  int m_iSelectedItem;
  CStdString m_startDirectory;
};