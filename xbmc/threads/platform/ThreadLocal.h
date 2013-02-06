

#pragma once

#if (defined TARGET_POSIX)
#include "threads/platform/pthreads/ThreadLocal.h"
#elif (defined TARGET_WINDOWS)
#include "threads/platform/win/ThreadLocal.h"
#endif
