#pragma once


#include "ImusicInfoTagLoader.h"
#include "cores/paplayer/TimidityCodec.h"

namespace MUSIC_INFO
{
  class CMusicInfoTagLoaderMidi : public IMusicInfoTagLoader
  {
  public:
    CMusicInfoTagLoaderMidi();
    virtual ~CMusicInfoTagLoaderMidi();
    virtual bool Load(const CStdString& strFileName, CMusicInfoTag& tag);
  };
}

