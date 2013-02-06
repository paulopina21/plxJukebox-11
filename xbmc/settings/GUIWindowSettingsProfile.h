#pragma once



#include "guilib/GUIWindow.h"

class CGUIWindowSettingsProfile :
      public CGUIWindow
{
public:
  CGUIWindowSettingsProfile(void);
  virtual ~CGUIWindowSettingsProfile(void);
  virtual bool OnMessage(CGUIMessage& message);

protected:
  virtual void OnInitWindow();
  CFileItemList *m_listItems;

  void OnPopupMenu(int iItem);
  void DoRename(int iItem);
  void DoOverwrite(int iItem);
  int GetSelectedItem();
  void LoadList();
  void SetLastLoaded();
  void ClearListItems();
};
