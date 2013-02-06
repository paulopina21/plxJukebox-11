

#ifndef __CORE_AUDIO_SOUND_MANAGER_H__
#define __CORE_AUDIO_SOUND_MANAGER_H__

#include "CoreAudio.h"

struct core_audio_sound;
struct core_audio_sound_event;

typedef core_audio_sound* CoreAudioSoundRef; // Opaque reference for clients

class CCoreAudioSoundManager
{
public:
  CCoreAudioSoundManager();
  ~CCoreAudioSoundManager();
  bool Initialize(CStdString deviceName);
  void Run();
  void Stop();
  CoreAudioSoundRef RegisterSound(const CStdString& fileName);
  void UnregisterSound(CoreAudioSoundRef soundRef);
  void PlaySound(CoreAudioSoundRef soundRef);
protected:
  core_audio_sound_event* m_pCurrentEvent;

  CCoreAudioDevice m_OutputDevice;
  CCoreAudioUnit m_OutputUnit;
  AudioStreamBasicDescription m_OutputFormat;
  bool m_RestartOutputUnit;
  
  core_audio_sound* LoadSoundFromFile(const CStdString& fileName);
  static OSStatus RenderCallback(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags, const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList *ioData);
  OSStatus OnRender(AudioUnitRenderActionFlags *ioActionFlags, const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList *ioData);  
  static OSStatus PropertyChangeCallback(AudioDeviceID inDevice, UInt32 inChannel, Boolean isInput, AudioDevicePropertyID inPropertyID, void* inClientData);
};

#endif // __CORE_AUDIO_SOUND_MANAGER_H__
