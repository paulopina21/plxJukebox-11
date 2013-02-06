

#include <DelayImp.h>
#include "DllPaths_win32.h"
#include "filesystem/SpecialProtocol.h"
#include "Application.h"
#include "windowing/WindowingFactory.h"

FARPROC WINAPI delayHookNotifyFunc (unsigned dliNotify, PDelayLoadInfo pdli)
{
  switch (dliNotify)
  {
    case dliNotePreLoadLibrary:
      if (stricmp(pdli->szDll, "libmicrohttpd-5.dll") == 0)
      {
        CStdString strDll = CSpecialProtocol::TranslatePath(DLL_PATH_LIBMICROHTTP);
        HMODULE hMod = LoadLibraryEx(strDll.c_str(), 0, LOAD_WITH_ALTERED_SEARCH_PATH);
        return (FARPROC)hMod;
      }
      if (stricmp(pdli->szDll, "ssh.dll") == 0)
      {
        CStdString strDll = CSpecialProtocol::TranslatePath("special://bin/system/ssh.dll");
        HMODULE hMod = LoadLibraryEx(strDll.c_str(), 0, LOAD_WITH_ALTERED_SEARCH_PATH);
        return (FARPROC)hMod;
      }
      if (stricmp(pdli->szDll, "sqlite3.dll") == 0)
      {
        CStdString strDll = CSpecialProtocol::TranslatePath("special://bin/system/sqlite3.dll");
        HMODULE hMod = LoadLibraryEx(strDll.c_str(), 0, LOAD_WITH_ALTERED_SEARCH_PATH);
        return (FARPROC)hMod;
      }
      if (stricmp(pdli->szDll, "libsamplerate-0.dll") == 0)
      {
        CStdString strDll = CSpecialProtocol::TranslatePath("special://bin/system/libsamplerate-0.dll");
        HMODULE hMod = LoadLibraryEx(strDll.c_str(), 0, LOAD_WITH_ALTERED_SEARCH_PATH);
        return (FARPROC)hMod;
      }
      if (stricmp(pdli->szDll, "dnssd.dll") == 0)
      {
        CStdString strDll = CSpecialProtocol::TranslatePath("special://bin/system/dnssd.dll");
        HMODULE hMod = LoadLibraryEx(strDll.c_str(), 0, LOAD_WITH_ALTERED_SEARCH_PATH);
        return (FARPROC)hMod;
      }
      break;
  }
  return NULL;
}

FARPROC WINAPI delayHookFailureFunc (unsigned dliNotify, PDelayLoadInfo pdli)
{
  switch (dliNotify)
  {
    case dliFailLoadLib:
      g_application.Stop(1);
      CStdString strError;
      strError.Format("Uh oh, can't load %s, exiting.", pdli->szDll);
      MessageBox(NULL, strError.c_str(), "RAVEN: Fatal Error", MB_OK|MB_ICONERROR);
      exit(1);
      break;
  }
  return NULL;
}

// assign hook functions
PfnDliHook __pfnDliNotifyHook2 = delayHookNotifyFunc;
PfnDliHook __pfnDliFailureHook2 = delayHookFailureFunc;