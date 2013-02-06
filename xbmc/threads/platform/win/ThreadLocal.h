

#pragma once

#include <windows.h>

namespace XbmcThreads
{
  /**
   * A thin wrapper around windows thread specific storage
   * functionality.
   */
  template <typename T> class ThreadLocal
  {
    DWORD key;
  public:
    inline ThreadLocal() { key = TlsAlloc(); }

    inline ~ThreadLocal() { TlsFree(key);  }

    inline void set(T* val) {  TlsSetValue(key,(LPVOID)val);  }

    inline T* get() { return (T*)TlsGetValue(key); }
  };
}

