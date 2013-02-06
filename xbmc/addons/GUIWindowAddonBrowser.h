#pragma once



#include "addons/Addon.h"
#include "windows/GUIMediaWindow.h"
#include "pictures/PictureThumbLoader.h"

class CFileItem;
class CFileItemList;

class CGUIWindowAddonBrowser : public CGUIMediaWindow
{
public:
  CGUIWindowAddonBrowser(void);
  virtual ~CGUIWindowAddonBrowser(void);
  virtual bool OnMessage(CGUIMessage& message);

  /*! \brief Popup a selection dialog with a list of addons of the given type
   \param type the type of addon wanted
   \param addonID [out] the addon ID of the selected item
   \param showNone whether there should be a "None" item in the list (defaults to false)
   \return 1 if an addon was selected, 2 if "Get More" was chosen, or 0 if an error occurred or if the selection process was cancelled
   */
  static int SelectAddonID(ADDON::TYPE type, CStdString &addonID, bool showNone = false);
  static int SelectAddonID(const std::vector<ADDON::TYPE> &types, CStdString &addonID, bool showNone = false);
  /*! \brief Popup a selection dialog with a list of addons of the given type
   \param type the type of addon wanted
   \param addonIDs [out] array of selected addon IDs
   \param showNone whether there should be a "None" item in the list (defaults to false)
   \param multipleSelection allow selection of multiple addons, if set to true showNone will automaticly switch to false
   \return 1 if an addon was selected or multiple selection was specified, 2 if "Get More" was chosen, or 0 if an error occurred or if the selection process was cancelled
   */
  static int SelectAddonID(ADDON::TYPE type, CStdStringArray &addonIDs, bool showNone = false, bool multipleSelection = true);
  static int SelectAddonID(const std::vector<ADDON::TYPE> &types, CStdStringArray &addonIDs, bool showNone = false, bool multipleSelection = true);
  
protected:
  /* \brief set label2 of an item based on the Addon.Status property
   \param item the item to update
   */
  void SetItemLabel2(CFileItemPtr item);

  virtual void GetContextButtons(int itemNumber, CContextButtons &buttons);
  virtual bool OnContextButton(int itemNumber, CONTEXT_BUTTON button);
  virtual bool OnClick(int iItem);
  virtual void UpdateButtons();
  virtual bool GetDirectory(const CStdString &strDirectory, CFileItemList &items);
  virtual bool Update(const CStdString &strDirectory);
  virtual CStdString GetStartFolder(const CStdString &dir);
private:
  CPictureThumbLoader m_thumbLoader;
};

