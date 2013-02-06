#ifndef SCRAPER_URL_H
#define SCRAPER_URL_H



#include <vector>
#include "StdString.h"

class TiXmlElement;
namespace XFILE { class CFileCurl; }

class CScraperUrl
{
public:
  CScraperUrl(const CStdString&);
  CScraperUrl(const TiXmlElement*);
  CScraperUrl();
  ~CScraperUrl();

  enum URLTYPES
  {
    URL_TYPE_GENERAL = 1,
    URL_TYPE_SEASON = 2
  };

  struct SUrlEntry
  {
    CStdString m_spoof;
    CStdString m_url;
    CStdString m_cache;
    URLTYPES m_type;
    bool m_post;
    bool m_isgz;
    int m_season;
  };

  bool Parse();
  bool ParseString(CStdString); // copies by intention
  bool ParseElement(const TiXmlElement*);
  bool ParseEpisodeGuide(CStdString strUrls); // copies by intention

  const SUrlEntry GetFirstThumb() const;
  const SUrlEntry GetSeasonThumb(int) const;

  /*! \brief fetch the full URL (including referrer) of a thumb
   \param URL entry to use to create the full URL
   \return the full URL, including referrer
   */
  static CStdString GetThumbURL(const CScraperUrl::SUrlEntry &entry);

  /*! \brief fetch the full URL (including referrer) of thumbs
   \param thumbs [out] vector of thumb URLs to fill
   \param season number of season that we want thumbs for, -1 indicates no season (the default)
   */
  void GetThumbURLs(std::vector<CStdString> &thumbs, int season = -1) const;
  void Clear();
  static bool Get(const SUrlEntry&, std::string&, XFILE::CFileCurl& http,
                 const CStdString& cacheContext);
  static bool DownloadThumbnail(const CStdString &thumb, const SUrlEntry& entry);

  CStdString m_xml;
  CStdString m_spoof; // for backwards compatibility only!
  CStdString strTitle;
  CStdString strId;
  double relevance;
  std::vector<SUrlEntry> m_url;
};

#endif


