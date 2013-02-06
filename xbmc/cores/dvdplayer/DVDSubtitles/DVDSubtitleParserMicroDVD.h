#pragma once



#include "DVDSubtitleParser.h"
#include "DVDSubtitleLineCollection.h"

class CDVDSubtitleParserMicroDVD : public CDVDSubtitleParserText
{
public:
  CDVDSubtitleParserMicroDVD(CDVDSubtitleStream* stream, const std::string& strFile);
  virtual ~CDVDSubtitleParserMicroDVD();

  virtual bool Open(CDVDStreamInfo &hints);
private:
  double m_framerate;
};
