

#include "emu_dummy.h"
#include "utils/log.h"

extern "C" void not_implement( const char* debuginfo)
{
  if (debuginfo)
  {
    CLog::Log(LOGDEBUG, "%s", (char*)debuginfo);
  }
}

