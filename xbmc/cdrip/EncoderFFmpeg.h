#ifndef _ENCODERFFMPEG_H
#define _ENCODERFFMPEG_H



#include "Encoder.h"
#include "DllAvFormat.h"
#include "DllAvCodec.h"
#include "DllAvUtil.h"

class CEncoderFFmpeg : public CEncoder
{
public:
  CEncoderFFmpeg();
  virtual ~CEncoderFFmpeg() {}
  bool Init(const char* strFile, int iInChannels, int iInRate, int iInBits);
  int Encode(int nNumBytesRead, uint8_t* pbtStream);
  bool Close();
  void AddTag(int key, const char* value);

private:
  DllAvCodec  m_dllAvCodec;
  DllAvUtil   m_dllAvUtil;
  DllAvFormat m_dllAvFormat;

  AVFormatContext  *m_Format;
  AVCodecContext   *m_CodecCtx;
  AVStream         *m_Stream;
  AVPacket          m_Pkt;
  unsigned char     m_BCBuffer[AVCODEC_MAX_AUDIO_FRAME_SIZE];
  static int        MuxerReadPacket(void *opaque, uint8_t *buf, int buf_size);
  void              SetTag(const CStdString tag, const CStdString value);


  unsigned int      m_NeededFrames;
  unsigned int      m_NeededBytes;
  uint8_t          *m_Buffer;
  unsigned int      m_BufferSize;

  bool WriteFrame();
};

#endif // _ENCODERFFMPEG_H
