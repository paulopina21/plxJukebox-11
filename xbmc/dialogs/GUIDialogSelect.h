#pragma once



#include "GUIDialogBoxBase.h"
#include "guilib/GUIListItem.h"
#include "GUIViewControl.h"

class CFileItem;
class CFileItemList;

class CGUIDialogSelect :
      public CGUIDialogBoxBase
{
public:
  CGUIDialogSelect(void);
  virtual ~CGUIDialogSelect(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnBack(int actionID);

  void Reset();
  void Add(const CStdString& strLabel);
  void Add(const CFileItem* pItem);
  void Add(const CFileItemList& items);
  void SetItems(CFileItemList* items);
  int GetSelectedLabel() const;
  const CStdString& GetSelectedLabelText();
  const CFileItemPtr GetSelectedItem();
  const CFileItemList& GetSelectedItems() const;
  void EnableButton(bool enable, int string);
  bool IsButtonPressed();
  void Sort(bool bSortOrder = true);
  void SetSelected(int iSelected);
  void SetUseDetails(bool useDetails);
  void SetMultiSelection(bool multiSelection) { m_multiSelection = multiSelection; };
protected:
  virtual CGUIControl *GetFirstFocusableControl(int id);
  virtual void OnWindowLoaded();
  virtual void OnInitWindow();

  bool m_bButtonEnabled;
  bool m_bButtonPressed;
  int m_iSelected;
  bool m_useDetails;
  bool m_multiSelection;

  CFileItemList* m_selectedItems;
  CFileItemList* m_vecListInternal;
  CFileItemList* m_vecList;
  CGUIViewControl m_viewControl;
};
