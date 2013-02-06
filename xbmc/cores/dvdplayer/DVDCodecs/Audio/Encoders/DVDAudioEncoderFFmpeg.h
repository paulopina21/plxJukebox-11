#pragma once


#include "IDVDAudioEncoder.h"
#include "DllAvCodec.h"
#include "DllAvFormat.h"
#include "DllAvUtil.h"

class CDVDAudioEncoderFFmpeg: public IDVDAudioEncoder
{
public:
  CDVDAudioEncoderFFmpeg();
  virtual ~CDVDAudioEncoderFFmpeg();
  virtual bool Initialize(unsigned int channels, enum PCMChannels *channelMap, unsigned int bitsPerSample, unsigned int sampleRate);
  virtual void Reset();

  /* returns this DSPs output format */
  virtual unsigned int      GetBitRate   ();
  virtual CodecID           GetCodecID   ();
  virtual unsigned int      GetPacketSize();

  /* add/get packets to/from the DSP */
  virtual int Encode (uint8_t *data, int size);
  virtual int GetData(uint8_t **data);
private:
  DllAvCodec m_dllAvCodec;
  DllAvCore  m_dllAvCore;
  DllAvUtil  m_dllAvUtil;

  AVCodecContext   *m_CodecCtx;
  AVAudioConvert   *m_AudioConvert;
  enum PCMChannels  m_ChannelMap[PCM_MAX_CH];
  CPCMRemap         m_Remap;
  uint8_t          *m_Buffer;
  uint8_t          *m_TmpBuffer;
  uint8_t          *m_TmpBuffer2;
  int               m_BufferSize;

  unsigned int      m_NeededFrames;
  unsigned int      m_NeededBytes;
  unsigned int      m_OutputBytes;
  unsigned int      m_BitsPerSample;
};

