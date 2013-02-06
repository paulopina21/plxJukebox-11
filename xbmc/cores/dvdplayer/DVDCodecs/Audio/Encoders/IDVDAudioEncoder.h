#pragma once


#include "utils/PCMRemap.h"
#include "DVDStreamInfo.h"

class IDVDAudioEncoder
{
public:
  IDVDAudioEncoder() {};
  virtual ~IDVDAudioEncoder() {};
  virtual bool Initialize(unsigned int channels, enum PCMChannels *channelMap, unsigned int bitsPerSample, unsigned int sampleRate) = 0;
  virtual void Reset() = 0;

  /* returns this DSPs output format */
  virtual unsigned int GetBitRate   () = 0;
  virtual CodecID      GetCodecID   () = 0;
  virtual unsigned int GetPacketSize() = 0;

  /* add/get packets to/from the DSP */
  virtual int Encode (uint8_t *data, int size) = 0;
  virtual int GetData(uint8_t **data) = 0;
};

