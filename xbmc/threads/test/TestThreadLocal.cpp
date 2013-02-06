

#include "threads/ThreadLocal.h"

#include "threads/Event.h"
#include <boost/test/unit_test.hpp>
#include <boost/thread/thread.hpp>

using namespace XbmcThreads;

bool destructorCalled = false;

class Thinggy
{
public:
  inline ~Thinggy() { destructorCalled = true; }
};

Thinggy* staticThinggy = NULL;
CEvent gate;
ThreadLocal<Thinggy> staticThreadLocal;

void cleanup()
{
  if (destructorCalled)
    staticThinggy = NULL;
  destructorCalled = false;
}

CEvent waiter;
class Runnable
{
public:
  bool waiting;
  bool threadLocalHadValue;
  ThreadLocal<Thinggy>& threadLocal;

  inline Runnable(ThreadLocal<Thinggy>& tl) : waiting(false), threadLocal(tl) {}
  inline void operator()()
  {
    staticThinggy = new Thinggy;
    staticThreadLocal.set(staticThinggy);
    waiting = true;
    gate.Set();
    waiter.Wait();
    waiting = false;

    threadLocalHadValue = staticThreadLocal.get() != NULL;
    gate.Set();
  }
};

class GlobalThreadLocal : public Runnable
{
public:
  GlobalThreadLocal() : Runnable(staticThreadLocal) {}
};

class StackThreadLocal : public Runnable
{
public:
  ThreadLocal<Thinggy> threadLocal;
  inline StackThreadLocal() : Runnable(threadLocal) {}
};

class HeapThreadLocal : public Runnable
{
public:
  ThreadLocal<Thinggy>* hthreadLocal;
  inline HeapThreadLocal() : Runnable(*(new ThreadLocal<Thinggy>)) { hthreadLocal = &threadLocal; }
  inline ~HeapThreadLocal() { delete hthreadLocal; }
};


BOOST_AUTO_TEST_CASE(TestSimpleThreadLocal)
{
  GlobalThreadLocal runnable;
  boost::thread(boost::ref(runnable));

  gate.Wait();
  BOOST_CHECK(runnable.waiting);
  BOOST_CHECK(staticThinggy != NULL);
  BOOST_CHECK(staticThreadLocal.get() == NULL);
  waiter.Set();
  gate.Wait();
  BOOST_CHECK(runnable.threadLocalHadValue);
  BOOST_CHECK(!destructorCalled);
  delete staticThinggy;
  BOOST_CHECK(destructorCalled);
  cleanup();
}

BOOST_AUTO_TEST_CASE(TestStackThreadLocal)
{
  StackThreadLocal runnable;
  boost::thread(boost::ref(runnable));

  gate.Wait();
  BOOST_CHECK(runnable.waiting);
  BOOST_CHECK(staticThinggy != NULL);
  BOOST_CHECK(runnable.threadLocal.get() == NULL);
  waiter.Set();
  gate.Wait();
  BOOST_CHECK(runnable.threadLocalHadValue);
  BOOST_CHECK(!destructorCalled);
  delete staticThinggy;
  BOOST_CHECK(destructorCalled);
  cleanup();
}

BOOST_AUTO_TEST_CASE(TestHeapThreadLocal)
{
  HeapThreadLocal runnable;
  boost::thread(boost::ref(runnable));

  gate.Wait();
  BOOST_CHECK(runnable.waiting);
  BOOST_CHECK(staticThinggy != NULL);
  BOOST_CHECK(runnable.threadLocal.get() == NULL);
  waiter.Set();
  gate.Wait();
  BOOST_CHECK(runnable.threadLocalHadValue);
  BOOST_CHECK(!destructorCalled);
  delete staticThinggy;
  BOOST_CHECK(destructorCalled);
  cleanup();
}

BOOST_AUTO_TEST_CASE(TestHeapThreadLocalDestroyed)
{
  {
    HeapThreadLocal runnable;
    boost::thread(boost::ref(runnable));

    gate.Wait();
    BOOST_CHECK(runnable.waiting);
    BOOST_CHECK(staticThinggy != NULL);
    BOOST_CHECK(runnable.threadLocal.get() == NULL);
    waiter.Set();
    gate.Wait();
    BOOST_CHECK(runnable.threadLocalHadValue);
    BOOST_CHECK(!destructorCalled);
  } // runnable goes out of scope

  // even though the threadlocal is gone ...
  BOOST_CHECK(!destructorCalled);
  delete staticThinggy;
  BOOST_CHECK(destructorCalled);
  cleanup();
}

