

#pragma once

#include "utils/StdString.h"

#ifdef HAS_SDL_AUDIO
#include <SDL/SDL_mixer.h>
#endif

class CGUISound
{
public:
  CGUISound();
  virtual ~CGUISound();

  bool        Load(const CStdString& strFile);
  void        Play();
  void        Stop();
  bool        IsPlaying();
  void        SetVolume(int level);
  void        Wait(uint32_t millis = 500);

private:
#ifdef _WIN32
  bool        LoadWav(const CStdString& strFile, WAVEFORMATEX* wfx, LPBYTE* ppWavData, int* pDataSize);
  bool        CreateBuffer(LPWAVEFORMATEX wfx, int iLength);
  bool        FillBuffer(LPBYTE pbData, int iLength);
  void        FreeBuffer();

  LPDIRECTSOUNDBUFFER m_soundBuffer;
#elif defined(HAS_SDL_AUDIO)
  Mix_Chunk* m_soundBuffer;
#else
  void *m_soundBuffer;
#endif
};
