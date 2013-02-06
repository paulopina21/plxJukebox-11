#ifndef SID_CODEC_H_
#define SID_CODEC_H_



#include "ICodec.h"
#include "DllSidplay2.h"

class SIDCodec : public ICodec
{
public:
  SIDCodec();
  virtual ~SIDCodec();

  virtual bool Init(const CStdString &strFile, unsigned int filecache);
  virtual void DeInit();
  virtual __int64 Seek(__int64 iSeekTime);
  virtual int ReadPCM(BYTE *pBuffer, int size, int *actualsize);
  virtual bool CanInit();

  virtual void SetTotalTime(__int64 totaltime)
  {
    m_TotalTime = totaltime*1000;
  }
private:
  DllSidplay2 m_dll;
  void* m_sid;
  int m_iTrack;
  __int64 m_iDataPos;
};

#endif

