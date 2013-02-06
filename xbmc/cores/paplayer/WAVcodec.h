

#pragma once
#include "ICodec.h"
#include "CachingCodec.h"
#include "ADPCMCodec.h"

class WAVCodec : public CachingCodec
{
public:
  WAVCodec();
  virtual ~WAVCodec();

  virtual bool Init(const CStdString &strFile, unsigned int filecache);
  virtual void DeInit();
  virtual __int64 Seek(__int64 iSeekTime);
  virtual int ReadPCM(BYTE *pBuffer, int size, int *actualsize);
  virtual int ReadSamples(float *pBuffer, int numsamples, int *actualsamples);
  virtual bool CanInit();
  virtual bool HasFloatData() const { return m_bHasFloat; }

private:
  bool m_bHasFloat;
  uint32_t m_iDataStart;
  uint32_t m_iDataLen;
  DWORD m_ChannelMask;
};

