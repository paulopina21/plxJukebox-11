#pragma once



#if (defined HAVE_CONFIG_H) && (!defined WIN32)
  #include "config.h"
#endif
#include "cores/AudioRenderers/IAudioRenderer.h"
#include "cores/IAudioCallback.h"
#include "threads/CriticalSection.h"
#include "PlatformDefs.h"

#ifndef _LINUX
enum CodecID;
#else
extern "C" {
#if (defined USE_EXTERNAL_FFMPEG)
  #if (defined HAVE_LIBAVCODEC_AVCODEC_H)
    #include <libavcodec/avcodec.h>
  #elif (defined HAVE_FFMPEG_AVCODEC_H)
    #include <ffmpeg/avcodec.h>
  #endif
#else
  #include "libavcodec/avcodec.h"
#endif
}
#endif
typedef struct stDVDAudioFrame DVDAudioFrame;

class CSingleLock;

class CDVDAudio
{
public:
  CDVDAudio(volatile bool& bStop);
  ~CDVDAudio();

  void RegisterAudioCallback(IAudioCallback* pCallback);
  void UnRegisterAudioCallback();

  void SetVolume(int iVolume);
  void SetDynamicRangeCompression(long drc);
  float GetCurrentAttenuation();
  void Pause();
  void Resume();
  bool Create(const DVDAudioFrame &audioframe, CodecID codec);
  bool IsValidFormat(const DVDAudioFrame &audioframe);
  void Destroy();
  DWORD AddPackets(const DVDAudioFrame &audioframe);
  double AddSilence(double delay);
  double GetDelay(); // returns the time it takes to play a packet if we add one at this time
  double GetCacheTime();  // returns total amount of data cached in audio output at this time
  double GetCacheTotal(); // returns total amount the audio device can buffer
  void Flush();
  void Finish();
  void Drain();

  IAudioRenderer* m_pAudioDecoder;
protected:
  DWORD AddPacketsRenderer(unsigned char* data, DWORD len, CSingleLock &lock);
  IAudioCallback* m_pCallback;
  BYTE* m_pBuffer; // should be [m_dwPacketSize]
  DWORD m_iBufferSize;
  DWORD m_dwPacketSize;
  CCriticalSection m_critSection;

  int m_iChannels;
  int m_iBitrate;
  int m_iBitsPerSample;
  double m_SecondsPerByte;
  bool m_bPassthrough;
  bool m_bPaused;

  volatile bool& m_bStop;
  //counter that will go from 0 to m_iSpeed-1 and reset, data will only be output when speedstep is 0
  //int m_iSpeedStep;
};
