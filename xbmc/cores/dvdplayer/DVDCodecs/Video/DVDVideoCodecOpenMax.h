#pragma once


#if defined(HAVE_LIBOPENMAX)

#include "DVDVideoCodec.h"

class COpenVideoMax;
class CDVDVideoCodecOpenMax : public CDVDVideoCodec
{
public:
  CDVDVideoCodecOpenMax();
  virtual ~CDVDVideoCodecOpenMax();

  // Required overrides
  virtual bool Open(CDVDStreamInfo &hints, CDVDCodecOptions &options);
  virtual void Dispose(void);
  virtual int  Decode(BYTE *pData, int iSize, double dts, double pts);
  virtual void Reset(void);
  virtual bool GetPicture(DVDVideoPicture *pDvdVideoPicture);
  virtual void SetDropState(bool bDrop);
  virtual const char* GetName(void) { return (const char*)m_pFormatName; }
  
protected:
  const char        *m_pFormatName;
  COpenMaxVideo     *m_omx_decoder;
  DVDVideoPicture   m_videobuffer;

  // bitstream to bytestream (Annex B) conversion support.
  bool bitstream_convert_init(void *in_extradata, int in_extrasize);
  bool bitstream_convert(BYTE* pData, int iSize, uint8_t **poutbuf, int *poutbuf_size);
  void bitstream_alloc_and_copy( uint8_t **poutbuf, int *poutbuf_size,
    const uint8_t *sps_pps, uint32_t sps_pps_size, const uint8_t *in, uint32_t in_size);

  typedef struct omx_bitstream_ctx {
      uint8_t  length_size;
      uint8_t  first_idr;
      uint8_t *sps_pps_data;
      uint32_t size;
  } omx_bitstream_ctx;

  uint32_t          m_sps_pps_size;
  omx_bitstream_ctx m_sps_pps_context;
  bool              m_convert_bitstream;
};

#endif
