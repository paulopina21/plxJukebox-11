

#pragma once

#if (defined HAVE_CONFIG_H) && (!defined WIN32)
  #include "config.h"
#endif
#ifndef _LINUX
enum StreamType;
enum CodecID;
#else
#include "DVDDemuxers/DVDDemux.h"
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

class CDemuxStream;

class CDVDStreamInfo
{
public:
  CDVDStreamInfo();
  CDVDStreamInfo(const CDVDStreamInfo &right, bool withextradata = true);
  CDVDStreamInfo(const CDemuxStream &right, bool withextradata = true);

  ~CDVDStreamInfo();

  void Clear(); // clears current information
  bool Equal(const CDVDStreamInfo &right, bool withextradata);
  bool Equal(const CDemuxStream &right, bool withextradata);

  void Assign(const CDVDStreamInfo &right, bool withextradata);
  void Assign(const CDemuxStream &right, bool withextradata);

  CodecID codec;
  StreamType type;
  bool software;  //force software decoding


  // VIDEO
  int fpsscale; // scale of 1000 and a rate of 29970 will result in 29.97 fps
  int fpsrate;
  int height; // height of the stream reported by the demuxer
  int width; // width of the stream reported by the demuxer
  float aspect; // display aspect as reported by demuxer
  bool vfr; // variable framerate
  bool stills; // there may be odd still frames in video
  int level; // encoder level of the stream reported by the decoder. used to qualify hw decoders.
  int profile; // encoder profile of the stream reported by the decoder. used to qualify hw decoders.
  bool ptsinvalid;  // pts cannot be trusted (avi's).
  bool forced_aspect; // aspect is forced from container

  // AUDIO
  int channels;
  int samplerate;
  int bitrate;
  int blockalign;
  int bitspersample;

  // SUBTITLE
  int identifier;

  // CODEC EXTRADATA
  void*        extradata; // extra data for codec to use
  unsigned int extrasize; // size of extra data
  unsigned int codec_tag; // extra identifier hints for decoding

  bool operator==(const CDVDStreamInfo& right)      { return Equal(right, true);}
  bool operator!=(const CDVDStreamInfo& right)      { return !Equal(right, true);}
  void operator=(const CDVDStreamInfo& right)       { Assign(right, true); }

  bool operator==(const CDemuxStream& right)      { return Equal( CDVDStreamInfo(right, true), true);}
  bool operator!=(const CDemuxStream& right)      { return !Equal( CDVDStreamInfo(right, true), true);}
  void operator=(const CDemuxStream& right)      { Assign(right, true); }

};
