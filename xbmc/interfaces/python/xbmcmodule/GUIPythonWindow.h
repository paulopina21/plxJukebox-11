#pragma once



#include "guilib/GUIWindow.h"
#include "threads/Event.h"

class PyXBMCAction
{
public:
  int param;
  void* pCallbackWindow;
  void* pObject;
  int controlId; // for XML window
#if defined(_LINUX) || defined(_WIN32)
  int type; // 0=Action, 1=Control;
#endif

  PyXBMCAction(void*& callback);
  virtual ~PyXBMCAction() ;
};

int Py_XBMC_Event_OnAction(void* arg);
int Py_XBMC_Event_OnControl(void* arg);

class CGUIPythonWindow : public CGUIWindow
{
public:
  CGUIPythonWindow(int id);
  virtual ~CGUIPythonWindow(void);
  virtual bool    OnMessage(CGUIMessage& message);
  virtual bool    OnAction(const CAction &action);
  virtual bool    OnBack(int actionID);
  void             SetCallbackWindow(void* state, void *object);
  void             WaitForActionEvent(unsigned int timeout);
  void             PulseActionEvent();
  void             SetDestroyAfterDeinit(bool destroy = true);
protected:
  virtual void     OnDeinitWindow(int nextWindowID = 0);
  void* pCallbackWindow;
  void* m_threadState;
  CEvent           m_actionEvent;
  bool             m_destroyAfterDeinit;
};
