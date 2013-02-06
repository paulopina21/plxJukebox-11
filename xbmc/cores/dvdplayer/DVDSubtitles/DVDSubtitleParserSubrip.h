#pragma once



#include "DVDSubtitleParser.h"
#include "DVDSubtitleLineCollection.h"

class CDVDSubtitleParserSubrip : public CDVDSubtitleParserText
{
public:
  CDVDSubtitleParserSubrip(CDVDSubtitleStream* pStream, const std::string& strFile);
  virtual ~CDVDSubtitleParserSubrip();

  virtual bool Open(CDVDStreamInfo &hints);
private:
};
