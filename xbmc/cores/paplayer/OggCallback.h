#pragma once



#include "DllVorbisfile.h"
#include "filesystem/File.h"

class COggCallback
{
public:
  COggCallback(XFILE::CFile& file);

  ov_callbacks Get(const CStdString& strFile);

  static size_t ReadCallback(void *ptr, size_t size, size_t nmemb, void *datasource);
  static int    SeekCallback(void *datasource, ogg_int64_t offset, int whence);
  static int    NoSeekCallback(void *datasource, ogg_int64_t offset, int whence);
  static int    CloseCallback(void *datasource);
  static long   TellCallback(void *datasource);
protected:
  XFILE::CFile& m_file;
};

