

#pragma once

#if (defined TARGET_POSIX)
#include "threads/platform/pthreads/Condition.h"
#elif (defined TARGET_WINDOWS)
#include "threads/platform/win/Condition.h"
#endif

