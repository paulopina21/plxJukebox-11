/*!
\file AudioContext.h
\brief
*/

#pragma once



#include "utils/StdString.h"

#define DSMIXBINTYPE_STANDARD 1
#define DSMIXBINTYPE_DMO 2
#define DSMIXBINTYPE_AAC 3
#define DSMIXBINTYPE_OGG 4
#define DSMIXBINTYPE_CUSTOM 5
#define DSMIXBINTYPE_STEREOALL 6
#define DSMIXBINTYPE_STEREOLEFT 7
#define DSMIXBINTYPE_STEREORIGHT 8

class CAudioContext
{
public:
  CAudioContext();
  virtual ~CAudioContext();

  void                        SetActiveDevice(int iDevice);
  int                         GetActiveDevice();

#ifdef HAS_AUDIO
  LPDIRECTSOUND8              GetDirectSoundDevice() { return m_pDirectSoundDevice; }
#ifdef HAS_AUDIO_PASS_THROUGH
  LPAC97MEDIAOBJECT           GetAc97Device() { return m_pAC97Device; }
#endif
#endif

  void                        SetupSpeakerConfig(int iChannels, bool& bAudioOnAllSpeakers, bool bIsMusic=true);
  bool                        IsAC3EncoderActive() const;
  bool                        IsPassthroughActive() const;

  enum AUDIO_DEVICE {NONE=0, DEFAULT_DEVICE, DIRECTSOUND_DEVICE, AC97_DEVICE, DIRECTSOUND_DEVICE_DIGITAL };
protected:
  void                         RemoveActiveDevice();

#ifdef HAS_AUDIO
#ifdef HAS_AUDIO_PASS_THROUGH
  LPAC97MEDIAOBJECT            m_pAC97Device;
#endif
  LPDIRECTSOUND8               m_pDirectSoundDevice;
#endif

  int                          m_iDevice;
  CStdString                   m_strDevice;
  bool                         m_bAC3EncoderActive;
};

extern CAudioContext g_audioContext;
