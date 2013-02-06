#pragma once



#include "GUIPythonWindow.h"
#include "windows/GUIMediaWindow.h"
#include "threads/Event.h"

int Py_XBMC_Event_OnClick(void* arg);
int Py_XBMC_Event_OnFocus(void* arg);
int Py_XBMC_Event_OnInit(void* arg);

class CGUIPythonWindowXML : public CGUIMediaWindow
{
public:
  CGUIPythonWindowXML(int id, CStdString strXML, CStdString strFallBackPath);
  virtual ~CGUIPythonWindowXML(void);
  virtual bool      OnMessage(CGUIMessage& message);
  virtual bool      OnAction(const CAction &action);
  virtual bool      OnBack(int actionID);
  virtual void      AllocResources(bool forceLoad = false);
  virtual void      FreeResources(bool forceUnLoad = false);
  void              Process(unsigned int currentTime, CDirtyRegionList &regions);
  void              WaitForActionEvent(unsigned int timeout);
  void              PulseActionEvent();
  void              AddItem(CFileItemPtr fileItem,int itemPosition);
  void              RemoveItem(int itemPosition);
  void              ClearList();
  CFileItemPtr      GetListItem(int position);
  int               GetListSize();
  int               GetCurrentListPosition();
  void              SetCurrentListPosition(int item);
  void              SetCallbackWindow(void* state, void* object);
  virtual bool      OnClick(int iItem);
  void              SetProperty(const CStdString &strProperty, const CStdString &strValue);
  void              SetDestroyAfterDeinit(bool destroy = true);

protected:
  virtual void     OnDeinitWindow(int nextWindowID = 0);
  virtual void     GetContextButtons(int itemNumber, CContextButtons &buttons);
  virtual bool     LoadXML(const CStdString &strPath, const CStdString &strPathLower);
  unsigned int     LoadScriptStrings();
  void             ClearScriptStrings();
  virtual bool     Update(const CStdString &strPath);
  void             SetupShares();
  void*            pCallbackWindow;
  void*            m_threadState;
  CEvent           m_actionEvent;
  bool             m_bRunning;
  CStdString       m_scriptPath;
  CStdString       m_mediaDir;
  bool             m_destroyAfterDeinit;
};

