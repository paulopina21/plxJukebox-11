#ifndef _DLL_TRACKER_H_
#define _DLL_TRACKER_H_



#include "threads/CriticalSection.h"
#include "PlatformDefs.h"
#ifdef _WIN32
#include "system.h" // for SOCKET
#endif

#include <list>
#include <map>

class DllLoader;

struct AllocLenCaller
{
  size_t   size;
  uintptr_t calleraddr;
};

enum TrackedFileType
{
  FILE_XBMC_OPEN,
  FILE_XBMC_FOPEN,
  FILE_OPEN,
  FILE_FOPEN
};

typedef struct _TrackedFile
{
  TrackedFileType type;
  uintptr_t handle;
  char* name;
} TrackedFile;

typedef std::map<uintptr_t, AllocLenCaller> DataList;
typedef std::map<uintptr_t, AllocLenCaller>::iterator DataListIter;

typedef std::list<TrackedFile*> FileList;
typedef std::list<TrackedFile*>::iterator FileListIter;

typedef std::list<HMODULE> DllList;
typedef std::list<HMODULE>::iterator DllListIter;

typedef std::list<uintptr_t> DummyList;
typedef std::list<uintptr_t>::iterator DummyListIter;

typedef std::list<SOCKET> SocketList;
typedef std::list<SOCKET>::iterator SocketListIter;

typedef std::list<HANDLE> HeapObjectList;
typedef std::list<HANDLE>::iterator HeapObjectListIter;

typedef std::map<uintptr_t, AllocLenCaller> VAllocList;
typedef std::map<uintptr_t, AllocLenCaller>::iterator  VAllocListIter;

typedef struct _DllTrackInfo
{
  DllLoader* pDll;
  uintptr_t lMinAddr;
  uintptr_t lMaxAddr;

  DataList dataList;

  // list with dll's that are loaded by this dll
  DllList dllList;

  // for dummy functions that are created if no exported function could be found
  DummyList dummyList;

  FileList fileList;
  SocketList socketList;

  HeapObjectList heapobjectList;

  VAllocList virtualList;
} DllTrackInfo;

class TrackedDllList : public std::list<DllTrackInfo*>, public CCriticalSection {};
typedef std::list<DllTrackInfo*>::iterator TrackedDllsIter;

#ifdef _cplusplus
extern "C"
{
#endif

extern CCriticalSection g_trackerLock;
extern TrackedDllList g_trackedDlls;

// add a dll for tracking
void tracker_dll_add(DllLoader* pDll);

// remove a dll, and free all its resources
void tracker_dll_free(DllLoader* pDll);

// sets the dll base address and size
void tracker_dll_set_addr(DllLoader* pDll, uintptr_t min, uintptr_t max);

// returns the name from the dll that contains this addres or "" if not found
char* tracker_getdllname(uintptr_t caller);

// returns a function pointer if there is one available for it, or NULL if not ofund
void* tracker_dll_get_function(DllLoader* pDll, char* sFunctionName);

DllTrackInfo* tracker_get_dlltrackinfo_byobject(DllLoader* pDll);

DllTrackInfo* tracker_get_dlltrackinfo(uintptr_t caller);

void tracker_dll_data_track(DllLoader* pDll, uintptr_t addr);

#ifdef _LINUX
#define _ReturnAddress() __builtin_return_address(0)
#endif

#ifdef _cplusplus
}
#endif

#ifndef _LINUX
extern "C" void * _ReturnAddress(void);
#pragma intrinsic(_ReturnAddress)
#endif

#endif // _DLL_TRACKER_H_
