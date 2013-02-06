

#include "utils/test/TestGlobalsHandlingPattern1.h"

#include <boost/test/unit_test.hpp>

using namespace xbmcutil;
using namespace test;

bool TestGlobalPattern1::ctorCalled = false;
bool TestGlobalPattern1::dtorCalled = false;

BOOST_AUTO_TEST_CASE(TestCtorPattern1)
{
  BOOST_CHECK(TestGlobalPattern1::ctorCalled);

  {
    boost::shared_ptr<TestGlobalPattern1> ptr = g_testGlobalPattern1Ref;
  }
}

