#pragma once



#include "threads/Condition.h"
#include "threads/SingleLock.h"
#include "threads/Helpers.h"

/**
 * A CSharedSection is a mutex that satisfies the Shared Lockable concept (see Lockables.h).
 */
class CSharedSection
{
  CCriticalSection sec;
  XbmcThreads::ConditionVariable actualCv;
  XbmcThreads::TightConditionVariable<XbmcThreads::InversePredicate<unsigned int&> > cond;

  unsigned int sharedCount;

public:
  inline CSharedSection() : cond(actualCv,XbmcThreads::InversePredicate<unsigned int&>(sharedCount)), sharedCount(0)  {}

  inline void lock() { CSingleLock l(sec); if (sharedCount) cond.wait(l); sec.lock(); }
  inline bool try_lock() { return (sec.try_lock() ? ((sharedCount == 0) ? true : (sec.unlock(), false)) : false); }
  inline void unlock() { sec.unlock(); }

  inline void lock_shared() { CSingleLock l(sec); sharedCount++; }
  inline bool try_lock_shared() { return (sec.try_lock() ? sharedCount++, sec.unlock(), true : false); }
  inline void unlock_shared() { CSingleLock l(sec); sharedCount--; if (!sharedCount) { cond.notifyAll(); } }
};

class CSharedLock : public XbmcThreads::SharedLock<CSharedSection>
{
public:
  inline CSharedLock(CSharedSection& cs) : XbmcThreads::SharedLock<CSharedSection>(cs) {}
  inline CSharedLock(const CSharedSection& cs) : XbmcThreads::SharedLock<CSharedSection>((CSharedSection&)cs) {}

  inline bool IsOwner() const { return owns_lock(); }
  inline void Enter() { lock(); }
  inline void Leave() { unlock(); }
};

class CExclusiveLock : public XbmcThreads::UniqueLock<CSharedSection>
{
public:
  inline CExclusiveLock(CSharedSection& cs) : XbmcThreads::UniqueLock<CSharedSection>(cs) {}
  inline CExclusiveLock(const CSharedSection& cs) : XbmcThreads::UniqueLock<CSharedSection> ((CSharedSection&)cs) {}

  inline bool IsOwner() const { return owns_lock(); }
  inline void Leave() { unlock(); }
  inline void Enter() { lock(); }
};

