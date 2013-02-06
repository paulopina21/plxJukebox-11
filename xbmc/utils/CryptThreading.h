

#pragma once

#include "utils/GlobalsHandling.h"
#include "threads/CriticalSection.h"

class CryptThreadingInitializer
{
  CCriticalSection** locks;
  int numlocks;
  CCriticalSection locksLock;

public:
  CryptThreadingInitializer();
  ~CryptThreadingInitializer();

  CCriticalSection* get_lock(int index);
};

XBMC_GLOBAL_REF(CryptThreadingInitializer,g_cryptThreadingInitializer);
#define g_cryptThreadingInitializer XBMC_GLOBAL_USE(CryptThreadingInitializer)
