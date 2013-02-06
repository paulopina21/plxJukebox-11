

#include "MusicAlbumInfo.h"
#include "addons/Scraper.h"
#include "utils/log.h"

using namespace std;
using namespace MUSIC_GRABBER;

CMusicAlbumInfo::CMusicAlbumInfo(const CStdString& strAlbumInfo, const CScraperUrl& strAlbumURL)
{
  m_strTitle2 = strAlbumInfo;
  m_albumURL = strAlbumURL;
  m_relevance = -1;
  m_bLoaded = false;
}

CMusicAlbumInfo::CMusicAlbumInfo(const CStdString& strAlbum, const CStdString& strArtist,
  const CStdString& strAlbumInfo, const CScraperUrl& strAlbumURL)
{
  m_album.strAlbum = strAlbum;
  m_album.strArtist = strArtist;
  m_strTitle2 = strAlbumInfo;
  m_albumURL = strAlbumURL;
  m_relevance = -1;
  m_bLoaded = false;
}

void CMusicAlbumInfo::SetAlbum(CAlbum& album)
{
  m_album = album;
  m_album.m_strDateOfRelease.Format("%i", album.iYear);
  m_strTitle2 = "";
  m_bLoaded = true;
}

bool CMusicAlbumInfo::Load(XFILE::CFileCurl& http, const ADDON::ScraperPtr& scraper)
{
  bool fSuccess = scraper->GetAlbumDetails(http, m_albumURL, m_album);
  if (fSuccess && m_strTitle2.empty())
    m_strTitle2 = m_album.strAlbum;
  SetLoaded(fSuccess);
  return fSuccess;
}

