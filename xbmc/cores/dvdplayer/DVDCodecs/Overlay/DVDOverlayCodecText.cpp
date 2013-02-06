

#include "system.h"
#include "DVDOverlayCodecText.h"
#include "DVDOverlayText.h"
#include "DVDStreamInfo.h"
#include "DVDCodecs/DVDCodecs.h"
#include "utils/log.h"
#include "cores/dvdplayer/DVDSubtitles/DVDSubtitleTagSami.h"

CDVDOverlayCodecText::CDVDOverlayCodecText() : CDVDOverlayCodec("Text Subtitle Decoder")
{
  m_pOverlay = NULL;
  m_bIsSSA = false;
}

CDVDOverlayCodecText::~CDVDOverlayCodecText()
{
  if(m_pOverlay)
    SAFE_RELEASE(m_pOverlay);
}

bool CDVDOverlayCodecText::Open(CDVDStreamInfo &hints, CDVDCodecOptions &options)
{
  m_bIsSSA = (hints.codec == CODEC_ID_SSA);
  if(hints.codec == CODEC_ID_TEXT || hints.codec == CODEC_ID_SSA)
    return true;
  return false;
}

void CDVDOverlayCodecText::Dispose()
{
  if(m_pOverlay)
    SAFE_RELEASE(m_pOverlay);
}

int CDVDOverlayCodecText::Decode(BYTE* data, int size, double pts, double duration)
{
  if(m_pOverlay)
    SAFE_RELEASE(m_pOverlay);

  m_pOverlay = new CDVDOverlayText();
  m_pOverlay->iPTSStartTime = 0;
  m_pOverlay->iPTSStopTime = 0;


  char *start, *end, *p;
  start = (char*)data;
  end   = (char*)data + size;
  p     = (char*)data;

  if (m_bIsSSA)
  {
    // currently just skip the prefixed ssa fields (8 fields)
    int nFieldCount = 8;
    while (nFieldCount > 0 && start < end)
    {
      if (*start == ',')
        nFieldCount--;

      start++;
      p++;
    }
  }

  CDVDSubtitleTagSami TagConv;
  bool Taginit = TagConv.Init();

  while(p<end)
  {
    if(*p == '{')
    {
      if(p>start)
      {
        if(Taginit)
          TagConv.ConvertLine(m_pOverlay, start, p-start);
        else
          m_pOverlay->AddElement(new CDVDOverlayText::CElementText(start, p-start));
      }
      start = p+1;

      while(*p != '}' && p<end)
        p++;

      char* override = (char*)malloc(p-start + 1);
      memcpy(override, start, p-start);
      override[p-start] = '\0';
      CLog::Log(LOGINFO, "%s - Skipped formatting tag %s", __FUNCTION__, override);
      free(override);

      start = p+1;
    }
    p++;
  }
  if(p>start)
  {
    if(Taginit)
    {
      TagConv.ConvertLine(m_pOverlay, start, p-start);
      TagConv.CloseTag(m_pOverlay);
    }
    else
      m_pOverlay->AddElement(new CDVDOverlayText::CElementText(start, p-start));
  }
  return OC_OVERLAY;
}

void CDVDOverlayCodecText::Reset()
{
  if(m_pOverlay)
    SAFE_RELEASE(m_pOverlay);
}

void CDVDOverlayCodecText::Flush()
{
  if(m_pOverlay)
    SAFE_RELEASE(m_pOverlay);
}

CDVDOverlay* CDVDOverlayCodecText::GetOverlay()
{
  if(m_pOverlay)
  {
    CDVDOverlay* overlay = m_pOverlay;
    m_pOverlay = NULL;
    return overlay;
  }
  return NULL;
}
