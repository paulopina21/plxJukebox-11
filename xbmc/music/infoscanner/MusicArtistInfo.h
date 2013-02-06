#pragma once



#include "music/Song.h"
#include "music/Artist.h"
#include "addons/Scraper.h"

class TiXmlDocument;
class CScraperUrl;

namespace MUSIC_GRABBER
{
class CMusicArtistInfo
{
public:
  CMusicArtistInfo() : m_bLoaded(false) {}
  CMusicArtistInfo(const CStdString& strArtist, const CScraperUrl& strArtistURL);
  virtual ~CMusicArtistInfo() {}
  bool Loaded() const { return m_bLoaded; }
  void SetLoaded() { m_bLoaded = true; }
  void SetArtist(const CArtist& artist);
  const CArtist& GetArtist() const { return m_artist; }
  CArtist& GetArtist() { return m_artist; }
  const CScraperUrl& GetArtistURL() const { return m_artistURL; }
  bool Load(XFILE::CFileCurl& http, const ADDON::ScraperPtr& scraper,
    const CStdString &strSearch);

protected:
  CArtist m_artist;
  CScraperUrl m_artistURL;
  bool m_bLoaded;
};
}
