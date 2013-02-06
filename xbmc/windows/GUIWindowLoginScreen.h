#pragma once



#include "guilib/GUIDialog.h"
#include "GUIViewControl.h"
#include "utils/Stopwatch.h"

class CFileItemList;

class CGUIWindowLoginScreen : public CGUIWindow
{
public:
  CGUIWindowLoginScreen(void);
  virtual ~CGUIWindowLoginScreen(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
  virtual bool OnBack(int actionID);
  virtual void FrameMove();
  virtual bool HasListItems() const { return true; };
  virtual CFileItemPtr GetCurrentListItem(int offset = 0);
  int GetViewContainerID() const { return m_viewControl.GetCurrentControl(); };
  static void LoadProfile(unsigned int profile);

protected:
  virtual void OnInitWindow();
  virtual void OnWindowLoaded();
  void Update();
  void SetLabel(int iControl, const CStdString& strLabel);

  bool OnPopupMenu(int iItem);
  CGUIViewControl m_viewControl;
  CFileItemList* m_vecItems;

  int m_iSelectedItem;
  CStopWatch watch;
};
