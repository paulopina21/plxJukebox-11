

#ifndef __ATOMICS_H__
#define __ATOMICS_H__

// TODO: Inline these methods
long cas(volatile long *pAddr, long expectedVal, long swapVal);
#if !defined(__ppc__) && !defined(__powerpc__) && !defined(__arm__)
long long cas2(volatile long long* pAddr, long long expectedVal, long long swapVal);
#endif
long AtomicIncrement(volatile long* pAddr);
long AtomicDecrement(volatile long* pAddr);
long AtomicAdd(volatile long* pAddr, long amount);
long AtomicSubtract(volatile long* pAddr, long amount);

class CAtomicSpinLock
{
public:
  CAtomicSpinLock(long& lock);
  ~CAtomicSpinLock();
private:
  long& m_Lock;
};


#endif // __ATOMICS_H__

