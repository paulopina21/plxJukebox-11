#pragma once



#include <assert.h>
#include "threads/Atomics.h"

template<typename T> struct IDVDResourceCounted
{
  IDVDResourceCounted() : m_refs(1) {}
  virtual ~IDVDResourceCounted() {}
  virtual T*   Acquire()
  {
    AtomicIncrement(&m_refs);
    return (T*)this;
  }

  virtual long Release()
  {
    long count = AtomicDecrement(&m_refs);
    assert(count >= 0);
    if (count == 0) delete (T*)this;
    return count;
  }
  long m_refs;
};
