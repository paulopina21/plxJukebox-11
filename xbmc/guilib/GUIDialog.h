/*!
\file GUIDialog.h
\brief
*/

#pragma once



#include "GUIWindow.h"
#include "Key.h"

/*!
 \ingroup winmsg
 \brief
 */
class CGUIDialog :
      public CGUIWindow
{
public:
  CGUIDialog(int id, const CStdString &xmlFile);
  virtual ~CGUIDialog(void);

  virtual bool OnAction(const CAction &action);
  virtual bool OnMessage(CGUIMessage& message);
  virtual void FrameMove();
  virtual void DoProcess(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();

  void DoModal(int iWindowID = WINDOW_INVALID, const CStdString &param = ""); // modal
  void Show(); // modeless
  
  virtual bool OnBack(int actionID);

  virtual bool IsDialogRunning() const { return m_active; };
  virtual bool IsDialog() const { return true;};
  virtual bool IsModalDialog() const { return m_bModal; };

  void SetAutoClose(unsigned int timeoutMs);
  void SetSound(bool OnOff) { m_enableSound = OnOff; };
  virtual bool IsSoundEnabled() const { return m_enableSound; };

protected:
  virtual void SetDefaults();
  virtual void OnWindowLoaded();
  virtual void UpdateVisibility();

  virtual void DoModal_Internal(int iWindowID = WINDOW_INVALID, const CStdString &param = ""); // modal
  virtual void Show_Internal(); // modeless
  virtual void OnDeinitWindow(int nextWindowID);

  bool m_wasRunning; ///< \brief true if we were running during the last DoProcess()
  bool m_bModal;
  bool m_autoClosing;
  bool m_enableSound;
  unsigned int m_showStartTime;
  unsigned int m_showDuration;
};
