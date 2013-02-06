

#include "stdio_utf8.h"
#include "utils/StdString.h"
#include "utils/CharsetConverter.h"

int remove_utf8(const char* __filename)
{
  CStdStringW filenameW;
  g_charsetConverter.utf8ToW(__filename, filenameW, false);
  return ::DeleteFileW(filenameW.c_str()) ? 0 : -1;
}

int rename_utf8(const char* __old, const char* __new)
{
  CStdStringW oldW, newW;
  g_charsetConverter.utf8ToW(__old, oldW, false);
  g_charsetConverter.utf8ToW(__new, newW, false);
  return ::MoveFileW(oldW.c_str(), newW.c_str()) ? 0 : -1;
}

FILE* fopen64_utf8(const char* __filename, const char* __modes)
{
  CStdStringW filenameW, modesW;
  g_charsetConverter.utf8ToW(__filename, filenameW, false);
  g_charsetConverter.utf8ToW(__modes, modesW, false);
  return _wfopen(filenameW.c_str(), modesW.c_str());
}

