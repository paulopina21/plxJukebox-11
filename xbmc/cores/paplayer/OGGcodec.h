#pragma once



#include "CachingCodec.h"
#include "DllVorbisfile.h"
#include "OggCallback.h"

class OGGCodec : public CachingCodec
{
public:
  OGGCodec();
  virtual ~OGGCodec();

  virtual bool Init(const CStdString &strFile, unsigned int filecache);
  virtual void DeInit();
  virtual __int64 Seek(__int64 iSeekTime);
  virtual int ReadPCM(BYTE *pBuffer, int size, int *actualsize);
  virtual bool CanInit();

private:
  COggCallback m_callback;
  void RemapChannels(short *SampleBuffer, int samples);

  DllVorbisfile m_dll;
  OggVorbis_File m_VorbisFile;
  double m_TimeOffset;
  int m_CurrentStream;
  bool m_inited;
};
