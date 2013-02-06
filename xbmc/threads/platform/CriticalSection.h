

#pragma once

#if (defined TARGET_POSIX)
#include "threads/platform/pthreads/CriticalSection.h"
#elif (defined TARGET_WINDOWS)
#include "threads/platform/win/CriticalSection.h"
#endif
