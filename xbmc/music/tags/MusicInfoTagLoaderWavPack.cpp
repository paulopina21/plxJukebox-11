

#include "MusicInfoTagLoaderWavPack.h"
#include "cores/paplayer/DVDPlayerCodec.h"


using namespace MUSIC_INFO;

CMusicInfoTagLoaderWAVPack::CMusicInfoTagLoaderWAVPack(void)
{}

CMusicInfoTagLoaderWAVPack::~CMusicInfoTagLoaderWAVPack()
{}

int CMusicInfoTagLoaderWAVPack::ReadDuration(const CStdString& strFileName)
{
  DVDPlayerCodec codec;
  if (codec.Init(strFileName, 4096))
  {
    return (int)((codec.m_TotalTime + 500) / 1000);
  }
  return 0;
}

bool CMusicInfoTagLoaderWAVPack::PrioritiseAPETags() const
{
  // WAVPack files always prioritize APEv2 tags over ID3 tags.
  return true;
}
