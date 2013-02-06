

#if (defined TARGET_POSIX)
#include "threads/platform/pthreads/Implementation.cpp"
#elif (defined TARGET_WINDOWS)
#include "threads/platform/win/Implementation.cpp"
#endif
