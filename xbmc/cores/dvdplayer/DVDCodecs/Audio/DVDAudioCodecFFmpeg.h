#pragma once



#include "DVDAudioCodec.h"
#include "DllAvCodec.h"
#include "DllAvCore.h"
#include "DllAvFormat.h"
#include "DllAvUtil.h"

class CDVDAudioCodecFFmpeg : public CDVDAudioCodec
{
public:
  CDVDAudioCodecFFmpeg();
  virtual ~CDVDAudioCodecFFmpeg();
  virtual bool Open(CDVDStreamInfo &hints, CDVDCodecOptions &options);
  virtual void Dispose();
  virtual int Decode(BYTE* pData, int iSize);
  virtual int GetData(BYTE** dst);
  virtual void Reset();
  virtual int GetChannels();
  virtual enum PCMChannels *GetChannelMap();
  virtual int GetSampleRate();
  virtual int GetBitsPerSample();
  virtual const char* GetName() { return "FFmpeg"; }
  virtual int GetBufferSize() { return m_iBuffered; }
  virtual int GetBitRate();

protected:
  AVCodecContext* m_pCodecContext;
  AVAudioConvert* m_pConvert;;
  enum AVSampleFormat m_iSampleFormat;
  enum PCMChannels m_channelMap[PCM_MAX_CH + 1];

  BYTE *m_pBuffer1;
  int   m_iBufferSize1;

  BYTE *m_pBuffer2;
  int   m_iBufferSize2;

  bool m_bOpenedCodec;
  int m_iBuffered;

  int     m_channels;
  int64_t m_layout;

  DllAvCodec m_dllAvCodec;
  DllAvCore m_dllAvCore;
  DllAvUtil m_dllAvUtil;

  void BuildChannelMap();
};

