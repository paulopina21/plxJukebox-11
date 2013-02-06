

#include "DVDSubtitleParserMPL2.h"
#include "DVDCodecs/Overlay/DVDOverlayText.h"
#include "DVDClock.h"
#include "utils/RegExp.h"
#include "DVDStreamInfo.h"
#include "utils/StdString.h"
#include "DVDSubtitleTagMicroDVD.h"

using namespace std;

CDVDSubtitleParserMPL2::CDVDSubtitleParserMPL2(CDVDSubtitleStream* stream, const string& filename)
    : CDVDSubtitleParserText(stream, filename)
{

}

CDVDSubtitleParserMPL2::~CDVDSubtitleParserMPL2()
{
  Dispose();
}

bool CDVDSubtitleParserMPL2::Open(CDVDStreamInfo &hints)
{
  if (!CDVDSubtitleParserText::Open())
    return false;

  // MPL2 is time-based, with 0.1s accuracy
  m_framerate = DVD_TIME_BASE / 10.0;

  char line[1024];

  CRegExp reg;
  if (!reg.RegComp("\\[([0-9]+)\\]\\[([0-9]+)\\]"))
    return false;
  CDVDSubtitleTagMicroDVD TagConv;

  while (m_pStream->ReadLine(line, sizeof(line)))
  {
    if ((strlen(line) > 0) && (line[strlen(line) - 1] == '\r'))
      line[strlen(line) - 1] = 0;

    int pos = reg.RegFind(line);
    if (pos > -1)
    {
      const char* text = line + pos + reg.GetFindLen();
      char* startFrame = reg.GetReplaceString("\\1");
      char* endFrame   = reg.GetReplaceString("\\2");
      CDVDOverlayText* pOverlay = new CDVDOverlayText();
      pOverlay->Acquire(); // increase ref count with one so that we can hold a handle to this overlay

      pOverlay->iPTSStartTime = m_framerate * atoi(startFrame);
      pOverlay->iPTSStopTime  = m_framerate * atoi(endFrame);

      TagConv.ConvertLine(pOverlay, text, strlen(text));

      free(startFrame);
      free(endFrame);

      m_collection.Add(pOverlay);
    }
  }

  return true;
}

