#ifndef __X_SYNC_UTILS_
#define __X_SYNC_UTILS_



#include "PlatformDefs.h"
#include "XHandlePublic.h"

#ifdef _LINUX

#define STATUS_WAIT_0 ((DWORD   )0x00000000L)
#define WAIT_FAILED   ((DWORD)0xFFFFFFFF)
#define WAIT_OBJECT_0 ((STATUS_WAIT_0 ) + 0 )
#define WAIT_TIMEOUT  258L
#define INFINITE    0xFFFFFFFF
#define STATUS_ABANDONED_WAIT_0 0x00000080
#define WAIT_ABANDONED         ((STATUS_ABANDONED_WAIT_0 ) + 0 )
#define WAIT_ABANDONED_0       ((STATUS_ABANDONED_WAIT_0 ) + 0 )

void GlobalMemoryStatusEx(LPMEMORYSTATUSEX lpBuffer);

#endif

#endif

