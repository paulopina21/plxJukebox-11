

#include "MusicInfoTagLoaderMPC.h"
#include "cores/paplayer/DVDPlayerCodec.h"


using namespace MUSIC_INFO;

CMusicInfoTagLoaderMPC::CMusicInfoTagLoaderMPC(void)
{}

CMusicInfoTagLoaderMPC::~CMusicInfoTagLoaderMPC()
{}

int CMusicInfoTagLoaderMPC::ReadDuration(const CStdString &strFileName)
{
  DVDPlayerCodec codec;
  if (codec.Init(strFileName, 4096))
  {
    return (int)((codec.m_TotalTime + 500) / 1000);
  }
  return 0;
}

