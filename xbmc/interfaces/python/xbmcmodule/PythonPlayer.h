

#pragma once

#include <Python.h>
#include "cores/IPlayer.h"


int Py_XBMC_Event_OnPlayBackStarted(void* arg);
int Py_XBMC_Event_OnPlayBackEnded(void* arg);
int Py_XBMC_Event_OnPlayBackStopped(void* arg);
int Py_XBMC_Event_OnPlayBackPaused(void* arg);
int Py_XBMC_Event_OnPlayBackResumed(void* arg);

class CPythonPlayer : public IPlayerCallback
{
public:
  CPythonPlayer();
  void    SetCallback(PyThreadState *state, PyObject *object);
  void    OnPlayBackEnded();
  void    OnPlayBackStarted();
  void    OnPlayBackPaused();
  void    OnPlayBackResumed();
  void    OnPlayBackStopped();
  void    OnQueueNextItem() {}; // unimplemented

  void    Acquire();
  void    Release();

  PyObject* m_callback;
  PyThreadState *m_state;
protected:
  virtual ~CPythonPlayer(void);
  long   m_refs;
};
