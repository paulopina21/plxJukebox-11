#pragma once



#include "DVDSubtitleParser.h"
#include "DVDSubtitleLineCollection.h"

class CDVDSubtitleParserVplayer : public CDVDSubtitleParserText
{
public:
  CDVDSubtitleParserVplayer(CDVDSubtitleStream* pStream, const std::string& strFile);
  virtual ~CDVDSubtitleParserVplayer();

  virtual bool Open(CDVDStreamInfo &hints);
private:
  double m_framerate;
};
