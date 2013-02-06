#pragma once



#include "ICodec.h"
#include "filesystem/File.h"

class CachingCodec : public ICodec
{
public:
  virtual ~CachingCodec() {}
  virtual int GetCacheLevel() { return -1; }

protected:
  XFILE::CFile m_file;
};
