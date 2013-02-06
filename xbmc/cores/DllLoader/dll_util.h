#ifndef _DLL_UTIL_H_
#define _DLL_UTIL_H_

#include <stdint.h>



#ifdef _cplusplus
extern "C"
{
#endif

uintptr_t create_dummy_function(const char* strDllName, const char* strFunctionName);
uintptr_t get_win_function_address(const char* strDllName, const char* strFunctionName);

#ifdef _cplusplus
}
#endif

#endif // _DLL_UTIL_H_
