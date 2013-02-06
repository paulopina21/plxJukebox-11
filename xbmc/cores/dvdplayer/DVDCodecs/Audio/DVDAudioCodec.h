#pragma once



#include "system.h"
#include "utils/PCMRemap.h"

#if (defined HAVE_CONFIG_H) && (!defined WIN32)
  #include "config.h"
#endif
#include <vector>
#include "DllAvCodec.h"

struct AVStream;

class CDVDStreamInfo;
class CDVDCodecOption;
typedef std::vector<CDVDCodecOption> CDVDCodecOptions;

class CDVDAudioCodec
{
public:

  CDVDAudioCodec() {}
  virtual ~CDVDAudioCodec() {}

  /*
   * Open the decoder, returns true on success
   */
  virtual bool Open(CDVDStreamInfo &hints, CDVDCodecOptions &options) = 0;

  /*
   * Dispose, Free all resources
   */
  virtual void Dispose() = 0;

  /*
   * returns bytes used or -1 on error
   *
   */
  virtual int Decode(BYTE* pData, int iSize) = 0;

  /*
   * returns nr of bytes used or -1 on error
   * the data is valid until the next Decode call
   */
  virtual int GetData(BYTE** dst) = 0;

  /*
   * resets the decoder
   */
  virtual void Reset() = 0;

  /*
   * returns the nr of channels for the decoded audio stream
   */
  virtual int GetChannels() = 0;

  /*
   * returns the channel mapping
   */
  virtual enum PCMChannels* GetChannelMap() = 0;

  /*
   * returns the samplerate for the decoded audio stream
   */
  virtual int GetSampleRate() = 0;

  /*
   * returns the bitspersample for the decoded audio stream (eg 16 bits)
   */
  virtual int GetBitsPerSample() = 0;

  /*
   * should return the average input bit rate 
   */
  virtual int GetBitRate() { return 0; }

  /*
   * returns if the codec requests to use passtrough
   */
  virtual bool NeedPassthrough() { return false; }

  /*
   * should return codecs name
   */
  virtual const char* GetName() = 0;

  /*
   * should return amount of data decoded has buffered in preparation for next audio frame
   */
  virtual int GetBufferSize() { return 0; }
};
