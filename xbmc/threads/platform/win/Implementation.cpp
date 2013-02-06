

#include "threads/Condition.h"

namespace XbmcThreads
{

  namespace intern
  {
    ConditionVariableVista::TakesCV ConditionVariableVista::InitializeConditionVariableProc;
    ConditionVariableVista::SleepCVCS ConditionVariableVista::SleepConditionVariableCSProc;
    ConditionVariableVista::TakesCV ConditionVariableVista::WakeConditionVariableProc;
    ConditionVariableVista::TakesCV ConditionVariableVista::WakeAllConditionVariableProc;

    bool ConditionVariableVista::setConditionVarFuncs()
    {
      HMODULE mod = GetModuleHandle("Kernel32");

      if (mod == NULL)
        return false;

      InitializeConditionVariableProc = (TakesCV)GetProcAddress(mod,"InitializeConditionVariable");
      if (InitializeConditionVariableProc == NULL)
        return false;
    
      SleepConditionVariableCSProc = (SleepCVCS)GetProcAddress(mod,"SleepConditionVariableCS");
      WakeAllConditionVariableProc = (TakesCV)GetProcAddress(mod,"WakeAllConditionVariable");
      WakeConditionVariableProc = (TakesCV)GetProcAddress(mod,"WakeConditionVariable");

      return SleepConditionVariableCSProc != NULL && 
        WakeAllConditionVariableProc != NULL &&
        WakeConditionVariableProc != NULL;
    }
  }

  bool ConditionVariable::getIsVista()
  {
    if (!isIsVistaSet)
    {
      isVista = intern::ConditionVariableVista::setConditionVarFuncs();
      isIsVistaSet = true;
    }

    return isVista;
  }

  bool ConditionVariable::isVista = getIsVista();
  // bss segment nulled out by loader.
  bool ConditionVariable::isIsVistaSet;
}
