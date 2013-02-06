#pragma once



#include "DVDSubtitleParser.h"
#include "DVDSubtitleLineCollection.h"
#include "DVDSubtitlesLibass.h"


class CDVDSubtitleParserSSA : public CDVDSubtitleParserText
{
public:
  CDVDSubtitleParserSSA(CDVDSubtitleStream* pStream, const std::string& strFile);
  virtual ~CDVDSubtitleParserSSA();

  virtual bool Open(CDVDStreamInfo &hints);
  virtual void Dispose();

private:
  CDVDSubtitlesLibass* m_libass;
};
