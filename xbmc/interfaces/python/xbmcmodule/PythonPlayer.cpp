

#include "pyutil.h"
#include "PythonPlayer.h"
#include "pythreadstate.h"
#include "../XBPython.h"
#include "threads/Atomics.h"

using namespace PYXBMC;

struct SPyEvent
{
  SPyEvent(CPythonPlayer* player
         , const char*    function)
  {
    m_player   = player;
    m_player->Acquire();
    m_function = function;
  }

  ~SPyEvent()
  {
    m_player->Release();
  }

  const char*    m_function;
  CPythonPlayer* m_player;
};

/*
 * called from python library!
 */
static int SPyEvent_Function(void* e)
{
  SPyEvent* object = (SPyEvent*)e;
  PyObject* ret    = NULL;

  if(object->m_player->m_callback)
    ret = PyObject_CallMethod(object->m_player->m_callback, (char*)object->m_function, NULL);

  if(ret)
  {
    Py_DECREF(ret);
  }

  CPyThreadState pyState;
  delete object;

  return 0;

}

CPythonPlayer::CPythonPlayer()
{
  m_callback = NULL;
  m_refs     = 1;
  g_pythonParser.RegisterPythonPlayerCallBack(this);
}

void CPythonPlayer::Release()
{
  if(AtomicDecrement(&m_refs) == 0)
    delete this;
}

void CPythonPlayer::Acquire()
{
  AtomicIncrement(&m_refs);
}

CPythonPlayer::~CPythonPlayer(void)
{
  g_pythonParser.UnregisterPythonPlayerCallBack(this);
}

void CPythonPlayer::OnPlayBackStarted()
{
  PyXBMC_AddPendingCall(m_state, SPyEvent_Function, new SPyEvent(this, "onPlayBackStarted"));
  g_pythonParser.PulseGlobalEvent();
}

void CPythonPlayer::OnPlayBackEnded()
{
  PyXBMC_AddPendingCall(m_state, SPyEvent_Function, new SPyEvent(this, "onPlayBackEnded"));
  g_pythonParser.PulseGlobalEvent();
}

void CPythonPlayer::OnPlayBackStopped()
{
  PyXBMC_AddPendingCall(m_state, SPyEvent_Function, new SPyEvent(this, "onPlayBackStopped"));
  g_pythonParser.PulseGlobalEvent();
}

void CPythonPlayer::OnPlayBackPaused()
{
  PyXBMC_AddPendingCall(m_state, SPyEvent_Function, new SPyEvent(this, "onPlayBackPaused"));
  g_pythonParser.PulseGlobalEvent();
}

void CPythonPlayer::OnPlayBackResumed()
{
  PyXBMC_AddPendingCall(m_state, SPyEvent_Function, new SPyEvent(this, "onPlayBackResumed"));
  g_pythonParser.PulseGlobalEvent();
}

void CPythonPlayer::SetCallback(PyThreadState *state, PyObject *object)
{
  /* python lock should be held */
  m_callback = object;
  m_state    = state;
}
