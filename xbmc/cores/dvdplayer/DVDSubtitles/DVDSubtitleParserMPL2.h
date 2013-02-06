#pragma once



#include "DVDSubtitleParser.h"
#include "DVDSubtitleLineCollection.h"

class CDVDSubtitleParserMPL2 : public CDVDSubtitleParserText
{
public:
  CDVDSubtitleParserMPL2(CDVDSubtitleStream* stream, const std::string& strFile);
  virtual ~CDVDSubtitleParserMPL2();

  virtual bool Open(CDVDStreamInfo &hints);
private:
  double m_framerate;
};
