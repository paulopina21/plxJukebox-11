#ifndef CUBE_CODEC_H_
#define CUBE_CODEC_H_



#include "ICodec.h"
#include "DllVGMStream.h"

class VGMCodec : public ICodec
{
public:
  VGMCodec();
  virtual ~VGMCodec();

  virtual bool Init(const CStdString &strFile, unsigned int filecache);
  virtual void DeInit();
  virtual __int64 Seek(__int64 iSeekTime);
  virtual int ReadPCM(BYTE *pBuffer, int size, int *actualsize);
  virtual bool CanInit();
  static bool IsSupportedFormat(const CStdString& strExt);

private:
  DllVGM m_dll;
  int m_vgm;
  __int64 m_iDataPos;
};

#endif

