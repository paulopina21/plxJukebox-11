#ifndef SCRAPER_PARSER_H
#define SCRAPER_PARSER_H



#include <vector>
#include "StdString.h"
#include "addons/IAddon.h"

#define MAX_SCRAPER_BUFFERS 20

namespace ADDON
{
  class CScraper;
}

class TiXmlElement;
class TiXmlDocument;

class CScraperSettings;

class CScraperParser
{
public:
  CScraperParser();
  CScraperParser(const CScraperParser& parser);
  ~CScraperParser();
  CScraperParser& operator= (const CScraperParser& parser);
  bool Load(const CStdString& strXMLFile);

  void Clear();
  const CStdString GetFilename() { return m_strFile; }
  CStdString GetSearchStringEncoding() const
    { return m_SearchStringEncoding; }
  const CStdString Parse(const CStdString& strTag,
                         ADDON::CScraper* scraper);

  void AddDocument(const TiXmlDocument* doc);

  CStdString m_param[MAX_SCRAPER_BUFFERS];

private:
  bool LoadFromXML();
  void ReplaceBuffers(CStdString& strDest);
  void ParseExpression(const CStdString& input, CStdString& dest, TiXmlElement* element, bool bAppend);
  void ParseNext(TiXmlElement* element);
  void Clean(CStdString& strDirty);
  /*! \brief Remove spaces, tabs, and newlines from a string
   \param string the string in question, which will be modified.
   */
  void RemoveWhiteSpace(CStdString &string);
  void ConvertJSON(CStdString &string);
  void ClearBuffers();
  void GetBufferParams(bool* result, const char* attribute, bool defvalue);
  void InsertToken(CStdString& strOutput, int buf, const char* token);

  TiXmlDocument* m_document;
  TiXmlElement* m_pRootElement;

  const char* m_SearchStringEncoding;

  CStdString m_strFile;
  ADDON::CScraper* m_scraper;
};

#endif


