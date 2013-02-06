

#pragma once

#include "utils/GlobalsHandling.h"

#include <iostream>

namespace xbmcutil
{
  namespace test
  {
    class TestGlobalPattern1
    {
    public:
      static bool ctorCalled;
      static bool dtorCalled;

      int somethingToAccess;

      TestGlobalPattern1() : somethingToAccess(0) { ctorCalled = true; }
      ~TestGlobalPattern1() 
      { 
        std::cout << "Clean shutdown of TestGlobalPattern1" << std::endl << std::flush;
        dtorCalled = true; 
      }

      void beHappy() { if (somethingToAccess) throw somethingToAccess; }
    };
  }
}

XBMC_GLOBAL_REF(xbmcutil::test::TestGlobalPattern1,g_testGlobalPattern1);
#define g_testGlobalPattern1 XBMC_GLOBAL_USE(xbmcutil::test::TestGlobalPattern1)

