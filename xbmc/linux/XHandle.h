#ifndef __X_HANDLE__
#define __X_HANDLE__



#ifndef _WIN32

#include <list>
#include <pthread.h>

#include "PlatformDefs.h"
#include "XHandlePublic.h"
#include "threads/Condition.h"
#include "threads/CriticalSection.h"
#include "utils/StdString.h"

struct CXHandle {

public:
  typedef enum { HND_NULL = 0, HND_FILE, HND_EVENT, HND_MUTEX, HND_THREAD, HND_FIND_FILE } HandleType;

  CXHandle();
  CXHandle(HandleType nType);
  CXHandle(const CXHandle &src);

  virtual ~CXHandle();
  void Init();
  inline HandleType GetType() { return m_type; }
  void ChangeType(HandleType newType);

  ThreadIdentifier      m_hThread;
  bool                  m_threadValid;
  XbmcThreads::ConditionVariable     *m_hCond;
  std::list<CXHandle*>  m_hParents;

#ifdef __APPLE__
  // Save the Mach thrad port, I don't think it can be obtained from
  // the pthread_t. We'll use it for querying timer information.
  //
  mach_port_t m_machThreadPort;
#endif

  // simulate mutex and critical section
  CCriticalSection *m_hMutex;
  int       RecursionCount;  // for mutex - for compatibility with WIN32 critical section
  pthread_t OwningThread;
  int       fd;
  bool      m_bManualEvent;
  time_t    m_tmCreation;
  CStdStringArray  m_FindFileResults;
  int              m_nFindFileIterator;
  CStdString       m_FindFileDir;
  off64_t          m_iOffset;
  bool             m_bCDROM;
  bool             m_bEventSet;
  int              m_nRefCount;
  CCriticalSection *m_internalLock;

  static void DumpObjectTracker();

protected:
  HandleType  m_type;
  static int m_objectTracker[10];

};

#endif

#endif

