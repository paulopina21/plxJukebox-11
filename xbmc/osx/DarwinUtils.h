
#ifndef _DARWIN_UTILS_H_
#define _DARWIN_UTILS_H_

#include <string>

#ifdef __cplusplus
extern "C"
{
#endif
  bool        DarwinIsAppleTV2(void);
  const char *GetDarwinVersionString(void);
  float       GetIOSVersion(void);
  int         GetDarwinFrameworkPath(bool forPython, char* path, uint32_t *pathsize);
  int         GetDarwinExecutablePath(char* path, uint32_t *pathsize);
  bool        DarwinHasVideoToolboxDecoder(void);
  int         DarwinBatteryLevel(void);
  void        DarwinSetScheduling(int message);
#ifdef __cplusplus
}
#endif

#endif
