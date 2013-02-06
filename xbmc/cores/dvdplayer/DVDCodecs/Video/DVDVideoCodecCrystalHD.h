

#pragma once

#if defined(HAVE_LIBCRYSTALHD)

#include "CrystalHD.h"
#include "DVDVideoCodec.h"

class CDVDVideoCodecCrystalHD : public CDVDVideoCodec
{
public:
  CDVDVideoCodecCrystalHD();
  virtual ~CDVDVideoCodecCrystalHD();

  // Required overrides
  virtual bool Open(CDVDStreamInfo &hints, CDVDCodecOptions &options);
  virtual void Dispose(void);
  virtual int  Decode(BYTE *pData, int iSize, double dts, double pts);
  virtual void Reset(void);
  virtual bool GetPicture(DVDVideoPicture *pDvdVideoPicture);
  virtual void SetDropState(bool bDrop);
  virtual const char* GetName(void) { return (const char*)m_pFormatName; }

protected:
  CCrystalHD      *m_Codec;
  bool            m_DropPictures;
  double          m_Duration;
  const char      *m_pFormatName;
  CRYSTALHD_CODEC_TYPE m_CodecType;
};

#endif
