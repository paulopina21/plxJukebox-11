

#include "system.h"
#include "DVDFactoryDemuxer.h"

#include "DVDInputStreams/DVDInputStream.h"
#include "DVDInputStreams/DVDInputStreamHttp.h"

#include "DVDDemuxFFmpeg.h"
#include "DVDDemuxShoutcast.h"
#ifdef HAS_FILESYSTEM_HTSP
#include "DVDDemuxHTSP.h"
#endif

using namespace std;

CDVDDemux* CDVDFactoryDemuxer::CreateDemuxer(CDVDInputStream* pInputStream)
{
  if (pInputStream->IsStreamType(DVDSTREAM_TYPE_HTTP))
  {
    CDVDInputStreamHttp* pHttpStream = (CDVDInputStreamHttp*)pInputStream;
    CHttpHeader *header = pHttpStream->GetHttpHeader();

    /* check so we got the meta information as requested in our http header */
    if( header->GetValue("icy-metaint").length() > 0 )
    {
      auto_ptr<CDVDDemuxShoutcast> demuxer(new CDVDDemuxShoutcast());
      if(demuxer->Open(pInputStream))
        return demuxer.release();
      else
        return NULL;
    }
  }

#ifdef HAS_FILESYSTEM_HTSP
  if (pInputStream->IsStreamType(DVDSTREAM_TYPE_HTSP))
  {
    auto_ptr<CDVDDemuxHTSP> demuxer(new CDVDDemuxHTSP());
    if(demuxer->Open(pInputStream))
      return demuxer.release();
    else
      return NULL;
  }
#endif

  auto_ptr<CDVDDemuxFFmpeg> demuxer(new CDVDDemuxFFmpeg());
  if(demuxer->Open(pInputStream))
    return demuxer.release();
  else
    return NULL;
}

