

#pragma once
#include "CachingCodec.h"

class PCMCodec : public CachingCodec
{
public:
  PCMCodec(void);
  virtual ~PCMCodec(void);
  virtual bool Init(const CStdString &strFile, unsigned int filecache);
  virtual void DeInit();
  virtual __int64 Seek(__int64 iSeekTime);
  virtual int ReadPCM(BYTE *pBuffer, int size, int *actualsize);
  virtual bool CanInit();
  virtual void SetMimeParams(const CStdString& strMimeParams);
private:
  int iBytesPerSecond;
};


