

#include "stat_utf8.h"
#include "utils/StdString.h"
#include "utils/CharsetConverter.h"

int stat64_utf8(const char* __file, struct stat64* __buf)
{
  CStdStringW fileW;
  g_charsetConverter.utf8ToW(__file, fileW, false);
  return _wstat64(fileW.c_str(), __buf);
}

