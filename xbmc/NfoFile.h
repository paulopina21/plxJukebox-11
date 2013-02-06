
// NfoFile.h: interface for the CNfoFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NfoFile_H__641CCF68_6D2A_426E_9204_C0E4BEF12D00__INCLUDED_)
#define AFX_NfoFile_H__641CCF68_6D2A_426E_9204_C0E4BEF12D00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tinyXML/tinyxml.h"
#include "addons/Scraper.h"
#include "utils/CharsetConverter.h"

class CNfoFile
{
public:
  CNfoFile() : m_doc(NULL), m_headofdoc(NULL) {}
  virtual ~CNfoFile() { Close(); }

  enum NFOResult
  {
    NO_NFO       = 0,
    FULL_NFO     = 1,
    URL_NFO      = 2,
    COMBINED_NFO = 3,
    ERROR_NFO    = 4
  };

  NFOResult Create(const CStdString&, ADDON::TYPE, int episode=-1,
                   const CStdString& strPath2="");
  template<class T>
    bool GetDetails(T& details,const char* document=NULL, bool prioritise=false)
  {
    TiXmlDocument doc;
    CStdString strDoc;
    if (document)
      strDoc = document;
    else
      strDoc = m_headofdoc;
    // try to load using string charset
    if (strDoc.Find("encoding=") == -1)
      g_charsetConverter.unknownToUTF8(strDoc);

    doc.Parse(strDoc.c_str());
    if (!doc.RootElement()) return false;
    return details.Load(doc.RootElement(), true, prioritise);
  }

  void Close();
  void SetScraperInfo(const ADDON::ScraperPtr& info) { m_info = info; }
  const ADDON::ScraperPtr& GetScraperInfo() const { return m_info; }
  const CScraperUrl &ScraperUrl() const { return m_scurl; }

private:
  char* m_doc;
  char* m_headofdoc;
  ADDON::ScraperPtr m_info;
  ADDON::TYPE m_type;
  CScraperUrl m_scurl;

  int Load(const CStdString&);
  int Scrape(ADDON::ScraperPtr& scraper);
  void AddScrapers(ADDON::VECADDONS& addons,
                   std::vector<ADDON::ScraperPtr>& vecScrapers);
};

#endif // !defined(AFX_NfoFile_H__641CCF68_6D2A_426E_9204_C0E4BEF12D00__INCLUDED_)
