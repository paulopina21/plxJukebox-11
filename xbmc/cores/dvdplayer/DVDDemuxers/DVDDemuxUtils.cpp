

#if (defined HAVE_CONFIG_H) && (!defined WIN32)
  #include "config.h"
#endif
#include "DVDDemuxUtils.h"
#include "DVDClock.h"
#include "utils/log.h"
extern "C" {
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

void CDVDDemuxUtils::FreeDemuxPacket(DemuxPacket* pPacket)
{
  if (pPacket)
  {
    try {
      if (pPacket->pData) _aligned_free(pPacket->pData);
      delete pPacket;
    }
    catch(...) {
      CLog::Log(LOGERROR, "%s - Exception thrown while freeing packet", __FUNCTION__);
    }
  }
}

DemuxPacket* CDVDDemuxUtils::AllocateDemuxPacket(int iDataSize)
{
  DemuxPacket* pPacket = new DemuxPacket;
  if (!pPacket) return NULL;

  try
  {
    memset(pPacket, 0, sizeof(DemuxPacket));

    if (iDataSize > 0)
    {
      // need to allocate a few bytes more.
      // From avcodec.h (ffmpeg)
      /**
        * Required number of additionally allocated bytes at the end of the input bitstream for decoding.
        * this is mainly needed because some optimized bitstream readers read
        * 32 or 64 bit at once and could read over the end<br>
        * Note, if the first 23 bits of the additional bytes are not 0 then damaged
        * MPEG bitstreams could cause overread and segfault
        */
      pPacket->pData =(BYTE*)_aligned_malloc(iDataSize + FF_INPUT_BUFFER_PADDING_SIZE, 16);
      if (!pPacket->pData)
      {
        FreeDemuxPacket(pPacket);
        return NULL;
      }

      // reset the last 8 bytes to 0;
      memset(pPacket->pData + iDataSize, 0, FF_INPUT_BUFFER_PADDING_SIZE);
    }

    // setup defaults
    pPacket->dts       = DVD_NOPTS_VALUE;
    pPacket->pts       = DVD_NOPTS_VALUE;
    pPacket->iStreamId = -1;
  }
  catch(...)
  {
    CLog::Log(LOGERROR, "%s - Exception thrown", __FUNCTION__);
    FreeDemuxPacket(pPacket);
    pPacket = NULL;
  }
  return pPacket;
}
