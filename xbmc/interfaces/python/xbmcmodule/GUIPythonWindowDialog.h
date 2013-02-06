#pragma once



#include "GUIPythonWindow.h"

class CApplicationMessenger;

class CGUIPythonWindowDialog : public CGUIPythonWindow
{
public:
  CGUIPythonWindowDialog(int id);
  virtual ~CGUIPythonWindowDialog(void);
  virtual bool    OnMessage(CGUIMessage& message);
  virtual bool    IsDialogRunning() const { return m_active; }
  virtual bool    IsDialog() const { return true;};
  virtual bool    IsModalDialog() const { return true; };

protected:
  friend class CApplicationMessenger;
  void Show_Internal(bool show = true);
  virtual void OnDeinitWindow(int nextWindowID = 0);
};
