

#include "MusicArtistInfo.h"
#include "addons/Scraper.h"
#include "utils/log.h"

using namespace std;
using namespace XFILE;
using namespace MUSIC_GRABBER;

CMusicArtistInfo::CMusicArtistInfo(const CStdString& strArtist, const CScraperUrl& strArtistURL)
{
  m_artist.strArtist = strArtist;
  m_artistURL = strArtistURL;
  m_bLoaded = false;
}

void CMusicArtistInfo::SetArtist(const CArtist& artist)
{
  m_artist = artist;
  m_bLoaded = true;
}

bool CMusicArtistInfo::Load(CFileCurl& http, const ADDON::ScraperPtr& scraper,
  const CStdString &strSearch)
{
  return m_bLoaded = scraper->GetArtistDetails(http, m_artistURL, strSearch, m_artist);
}

