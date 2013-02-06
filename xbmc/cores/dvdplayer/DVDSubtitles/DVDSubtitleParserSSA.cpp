

#include "DVDSubtitleParserSSA.h"
#include "DVDCodecs/Overlay/DVDOverlaySSA.h"
#include "DVDClock.h"
#include "utils/log.h"

using namespace std;

CDVDSubtitleParserSSA::CDVDSubtitleParserSSA(CDVDSubtitleStream* pStream, const string& strFile)
    : CDVDSubtitleParserText(pStream, strFile)
{
  m_libass = new CDVDSubtitlesLibass();
}

CDVDSubtitleParserSSA::~CDVDSubtitleParserSSA()
{
  Dispose();
}

bool CDVDSubtitleParserSSA::Open(CDVDStreamInfo &hints)
{

  if (!CDVDSubtitleParserText::Open())
    return false;
  if(!m_libass->CreateTrack((char* )m_pStream->m_stringstream.str().c_str()))
    return false;

  //Creating the overlays by going through the list of ass_events
  ASS_Event* assEvent = m_libass->GetEvents();
  int numEvents = m_libass->GetNrOfEvents();

  for(int i=0; i < numEvents; i++)
  {
    ASS_Event* curEvent =  (assEvent+i);
    if (curEvent)
    {
      CDVDOverlaySSA* overlay = new CDVDOverlaySSA(m_libass);
      overlay->Acquire(); // increase ref count with one so that we can hold a handle to this overlay

      overlay->iPTSStartTime = (double)curEvent->Start * (DVD_TIME_BASE / 1000);
      overlay->iPTSStopTime  = (double)(curEvent->Start + curEvent->Duration) * (DVD_TIME_BASE / 1000);

      overlay->replace = true;
      m_collection.Add(overlay);
    }
  }
  m_collection.Sort();
  return true;
}

void CDVDSubtitleParserSSA::Dispose()
{
  if(m_libass)
  {
    SAFE_RELEASE(m_libass);
    CLog::Log(LOGINFO, "SSA Parser: Releasing reference to ASS Library");
  }
  CDVDSubtitleParserCollection::Dispose();
}
