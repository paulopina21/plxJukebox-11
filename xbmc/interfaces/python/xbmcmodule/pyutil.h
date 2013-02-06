

#include <Python.h>

#include "utils/StdString.h"

#ifdef __cplusplus
extern "C" {
#endif

// credits and version information
#define PY_XBMC_AUTHOR    "J. Mulder <darkie@xbmc.org>"
#define PY_XBMC_CREDITS   "XBMC TEAM."
#define PY_XBMC_PLATFORM  "XBOX"

namespace PYXBMC
{
  int   PyXBMCGetUnicodeString(std::string& buf, PyObject* pObject, int pos = -1);
  void  PyXBMCGUILock();
  void  PyXBMCGUIUnlock();
  const char* PyXBMCGetDefaultImage(char* controlType, char* textureType, char* cDefault);
  bool  PyXBMCWindowIsNull(void* pWindow);

  void  PyXBMCInitializeTypeObject(PyTypeObject* type_object);
  void  PyXBMCWaitForThreadMessage(int message, int param1, int param2);
}

// Python doesn't play nice with PyXBMC_AddPendingCall
// and PyXBMC_MakePendingCalls as it only allows them from
// the main python thread, which isn't what we want, so we have our own versions.

#define PyXBMC_AddPendingCall _PyXBMC_AddPendingCall
#define PyXBMC_MakePendingCalls _PyXBMC_MakePendingCalls
#define PyXBMC_ClearPendingCalls _PyXBMC_ClearPendingCalls

void _PyXBMC_AddPendingCall(PyThreadState* state, int(*func)(void*), void *arg);
void _PyXBMC_MakePendingCalls();
void _PyXBMC_ClearPendingCalls(PyThreadState* state);

#ifdef __cplusplus
}
#endif
