#pragma once



#include "DVDSubtitleParser.h"
#include "DVDSubtitleLineCollection.h"
class CDVDOverlayText;
class CRegExp;

class CDVDSubtitleParserSami : public CDVDSubtitleParserText
{
public:
  CDVDSubtitleParserSami(CDVDSubtitleStream* pStream, const std::string& strFile);
  virtual ~CDVDSubtitleParserSami();
  virtual bool Open(CDVDStreamInfo &hints);
};
