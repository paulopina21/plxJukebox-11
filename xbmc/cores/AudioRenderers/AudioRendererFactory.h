
#ifndef __AUDIO_RENDERER_FACTORY_H__
#define __AUDIO_RENDERER_FACTORY_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IAudioRenderer.h"
#include "cores/IAudioCallback.h"

class CAudioRendererFactory
{
public:
  static IAudioRenderer *Create(IAudioCallback* pCallback, int iChannels, enum PCMChannels *channelMap, unsigned int uiSamplesPerSec, unsigned int uiBitsPerSample, bool bResample, bool bIsMusic, IAudioRenderer::EEncoded encoded = IAudioRenderer::ENCODED_NONE);
  static void EnumerateAudioSinks(AudioSinkList& vAudioSinks, bool passthrough);
private:
  static IAudioRenderer *CreateFromUri(const CStdString &soundsystem, CStdString &renderer);
};
#endif
