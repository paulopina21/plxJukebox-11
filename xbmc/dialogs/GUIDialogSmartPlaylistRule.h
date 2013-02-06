#pragma once



#include "guilib/GUIDialog.h"
#include "playlists/SmartPlayList.h"

class CGUIDialogSmartPlaylistRule :
      public CGUIDialog
{
public:
  CGUIDialogSmartPlaylistRule(void);
  virtual ~CGUIDialogSmartPlaylistRule(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnBack(int actionID);
  virtual void OnInitWindow();

  static bool EditRule(CSmartPlaylistRule &rule, const CStdString& type="songs");

protected:
  void OnField();
  void OnOperator();
  void OnOK();
  void OnCancel();
  void UpdateButtons();
  void AddOperatorLabel(CSmartPlaylistRule::SEARCH_OPERATOR op);
  void OnBrowse();

  CSmartPlaylistRule m_rule;
  bool m_cancelled;
  CStdString m_type;
};
