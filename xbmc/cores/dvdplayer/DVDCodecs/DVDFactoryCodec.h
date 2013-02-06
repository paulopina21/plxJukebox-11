#pragma once



#include <vector>

class CDVDVideoCodec;
class CDVDAudioCodec;
class CDVDOverlayCodec;

class CDemuxStreamVideo;
class CDVDStreamInfo;
class CDVDCodecOption;
typedef std::vector<CDVDCodecOption> CDVDCodecOptions;

class CDVDFactoryCodec
{
public:
  static CDVDVideoCodec* CreateVideoCodec(CDVDStreamInfo &hint, unsigned int surfaces = 0);
  static CDVDAudioCodec* CreateAudioCodec(CDVDStreamInfo &hint, bool passthrough = true );
  static CDVDOverlayCodec* CreateOverlayCodec(CDVDStreamInfo &hint );

  static CDVDAudioCodec* OpenCodec(CDVDAudioCodec* pCodec, CDVDStreamInfo &hint, CDVDCodecOptions &options );
  static CDVDVideoCodec* OpenCodec(CDVDVideoCodec* pCodec, CDVDStreamInfo &hint, CDVDCodecOptions &options );
  static CDVDOverlayCodec* OpenCodec(CDVDOverlayCodec* pCodec, CDVDStreamInfo &hint, CDVDCodecOptions &options );
};

