#pragma once



#if (defined HAVE_CONFIG_H) && (!defined WIN32)
  #include "config.h"
#endif
// enum CodecID

#include <string>
#include <vector>

extern "C" {
#ifndef HAVE_MMX
#define HAVE_MMX
#endif
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
#ifndef __GNUC__
#pragma warning(disable:4244)
#endif
#if (defined USE_EXTERNAL_FFMPEG)
  #if (defined HAVE_LIBAVCODEC_AVCODEC_H)
    #include <libavcodec/avcodec.h>
  #else
    #include <ffmpeg/avcodec.h>
  #endif
#else
  #include "libavcodec/avcodec.h"
#endif
}

// 0x100000 is the video starting range

// 0x200000 is the audio starting range

// special options that can be passed to a codec
class CDVDCodecOption
{
public:
  CDVDCodecOption(std::string name, std::string value) { m_name = name; m_value = value; }
  std::string m_name;
  std::string m_value;
};
typedef std::vector<CDVDCodecOption> CDVDCodecOptions;
