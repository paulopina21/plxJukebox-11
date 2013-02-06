#pragma once



#include "../DVDCodecs/Overlay/DVDOverlay.h"
#include "DVDSubtitleStream.h"
#include "DVDSubtitleLineCollection.h"

#include <string>

class CDVDStreamInfo;

class CDVDSubtitleParser
{
public:
  virtual ~CDVDSubtitleParser() {}
  virtual bool Open(CDVDStreamInfo &hints) = 0;
  virtual void Dispose() = 0;
  virtual void Reset() = 0;
  virtual CDVDOverlay* Parse(double iPts) = 0;
};

class CDVDSubtitleParserCollection
  : public CDVDSubtitleParser
{
public:
  CDVDSubtitleParserCollection(const std::string& strFile)
  {
    m_filename = strFile;
  }
  virtual ~CDVDSubtitleParserCollection() { }
  virtual CDVDOverlay* Parse(double iPts) { return m_collection.Get(iPts); }
  virtual void         Reset()            { m_collection.Reset(); }
  virtual void         Dispose()          { m_collection.Clear(); }

protected:
  CDVDSubtitleLineCollection m_collection;
  std::string                m_filename;
};

class CDVDSubtitleParserText
     : public CDVDSubtitleParserCollection
{
public:
  CDVDSubtitleParserText(CDVDSubtitleStream* stream, const std::string& filename)
    : CDVDSubtitleParserCollection(filename)
  {
    m_pStream  = stream;
  }

  virtual ~CDVDSubtitleParserText()
  {
    if(m_pStream)
      delete m_pStream;
  }

protected:

  bool Open()
  {
    if(m_pStream)
    {
      if(m_pStream->Seek(0, SEEK_SET) == 0)
        return true;
    }
    else
      m_pStream = new CDVDSubtitleStream();

    return m_pStream->Open(m_filename);
  }

  CDVDSubtitleStream* m_pStream;
};
