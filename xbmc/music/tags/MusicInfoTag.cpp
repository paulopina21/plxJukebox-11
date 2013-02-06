

#include "MusicInfoTag.h"
#include "music/Album.h"
#include "utils/StringUtils.h"
#include "settings/AdvancedSettings.h"
#include "utils/Variant.h"

using namespace MUSIC_INFO;

CMusicInfoTag::CMusicInfoTag(void)
{
  Clear();
}

CMusicInfoTag::CMusicInfoTag(const CMusicInfoTag& tag)
{
  *this = tag;
}

CMusicInfoTag::~CMusicInfoTag()
{}

const CMusicInfoTag& CMusicInfoTag::operator =(const CMusicInfoTag& tag)
{
  if (this == &tag) return * this;

  m_strURL = tag.m_strURL;
  m_strArtist = tag.m_strArtist;
  m_strAlbumArtist = tag.m_strAlbumArtist;
  m_strAlbum = tag.m_strAlbum;
  m_strGenre = tag.m_strGenre;
  m_strTitle = tag.m_strTitle;
  m_strComment = tag.m_strComment;
  m_strLyrics = tag.m_strLyrics;
  m_strLastPlayed = tag.m_strLastPlayed;
  m_iDuration = tag.m_iDuration;
  m_iTrack = tag.m_iTrack;
  m_bLoaded = tag.m_bLoaded;
  m_rating = tag.m_rating;
  m_listeners = tag.m_listeners;
  m_iTimesPlayed = tag.m_iTimesPlayed;
  m_iDbId = tag.m_iDbId;
  m_iArtistId = tag.m_iArtistId;
  m_iAlbumId = tag.m_iAlbumId;
  m_strLabel = tag.m_strLabel; // Laureon: Added
  m_strISRC = tag.m_strISRC; // Laureon: Added
  memcpy(&m_dwReleaseDate, &tag.m_dwReleaseDate, sizeof(m_dwReleaseDate) );
  return *this;
}

bool CMusicInfoTag::operator !=(const CMusicInfoTag& tag) const
{
  if (this == &tag) return false;
  if (m_strURL != tag.m_strURL) return true;
  if (m_strTitle != tag.m_strTitle) return true;
  if (m_strArtist != tag.m_strArtist) return true;
  if (m_strAlbumArtist != tag.m_strAlbumArtist) return true;
  if (m_strAlbum != tag.m_strAlbum) return true;
  if (m_iDuration != tag.m_iDuration) return true;
  if (m_iTrack != tag.m_iTrack) return true;
  if (m_strISRC != tag.m_strISRC) return true; // Laureon: Added
  return false;
}

int CMusicInfoTag::GetTrackNumber() const
{
  return (m_iTrack & 0xffff);
}

int CMusicInfoTag::GetDiscNumber() const
{
  return (m_iTrack >> 16);
}

int CMusicInfoTag::GetTrackAndDiskNumber() const
{
  return m_iTrack;
}

int CMusicInfoTag::GetDuration() const
{
  return m_iDuration;
}

int CMusicInfoTag::GetArtistID() const {
  return m_iArtistId;
}

int CMusicInfoTag::GetAlbumID() const {
  return m_iAlbumId;
}

const CStdString& CMusicInfoTag::GetTitle() const
{
  return m_strTitle;
}

const CStdString& CMusicInfoTag::GetURL() const
{
  return m_strURL;
}

const CStdString& CMusicInfoTag::GetArtist() const
{
  return m_strArtist;
}

const CStdString& CMusicInfoTag::GetAlbum() const
{
  return m_strAlbum;
}

const CStdString& CMusicInfoTag::GetAlbumArtist() const
{
  return m_strAlbumArtist;
}

const CStdString& CMusicInfoTag::GetGenre() const
{
  return m_strGenre;
}

void CMusicInfoTag::GetReleaseDate(SYSTEMTIME& dateTime) const
{
  memcpy(&dateTime, &m_dwReleaseDate, sizeof(m_dwReleaseDate) );
}

int CMusicInfoTag::GetYear() const
{
  return m_dwReleaseDate.wYear;
}

long CMusicInfoTag::GetDatabaseId() const
{
  return m_iDbId;
}

CStdString CMusicInfoTag::GetYearString() const
{
  CStdString strReturn;
  strReturn.Format("%i", m_dwReleaseDate.wYear);
  return m_dwReleaseDate.wYear ? strReturn : "";
}

const CStdString &CMusicInfoTag::GetComment() const
{
  return m_strComment;
}

const CStdString &CMusicInfoTag::GetLyrics() const
{
  return m_strLyrics;
}

char CMusicInfoTag::GetRating() const
{
  return m_rating;
}

int CMusicInfoTag::GetListeners() const
{
 return m_listeners;
}

int CMusicInfoTag::GetPlayCount() const
{
  return m_iTimesPlayed;
}

const CStdString &CMusicInfoTag::GetLastPlayed() const
{
  return m_strLastPlayed;
}

void CMusicInfoTag::SetURL(const CStdString& strURL)
{
  m_strURL = strURL;
}

void CMusicInfoTag::SetTitle(const CStdString& strTitle)
{
  m_strTitle = Trim(strTitle);
}

void CMusicInfoTag::SetArtist(const CStdString& strArtist)
{
  m_strArtist = Trim(strArtist);
}

void CMusicInfoTag::SetArtistId(const int iArtistId)
{
  m_iArtistId = iArtistId;
}

void CMusicInfoTag::SetAlbum(const CStdString& strAlbum)
{
  m_strAlbum = Trim(strAlbum);
}

void CMusicInfoTag::SetAlbumId(const int iAlbumId)
{
  m_iAlbumId = iAlbumId;
}

void CMusicInfoTag::SetAlbumArtist(const CStdString& strAlbumArtist)
{
  m_strAlbumArtist = Trim(strAlbumArtist);
}

void CMusicInfoTag::SetGenre(const CStdString& strGenre)
{
  m_strGenre = Trim(strGenre);
}

void CMusicInfoTag::SetYear(int year)
{
  memset(&m_dwReleaseDate, 0, sizeof(m_dwReleaseDate) );
  m_dwReleaseDate.wYear = year;
}

void CMusicInfoTag::SetDatabaseId(long id)
{
  m_iDbId = id;
}

void CMusicInfoTag::SetReleaseDate(SYSTEMTIME& dateTime)
{
  memcpy(&m_dwReleaseDate, &dateTime, sizeof(m_dwReleaseDate) );
}

void CMusicInfoTag::SetTrackNumber(int iTrack)
{
  m_iTrack = (m_iTrack & 0xffff0000) | (iTrack & 0xffff);
}

void CMusicInfoTag::SetPartOfSet(int iPartOfSet)
{
  m_iTrack = (m_iTrack & 0xffff) | (iPartOfSet << 16);
}

void CMusicInfoTag::SetTrackAndDiskNumber(int iTrackAndDisc)
{
  m_iTrack=iTrackAndDisc;
}

void CMusicInfoTag::SetDuration(int iSec)
{
  m_iDuration = iSec;
}

void CMusicInfoTag::SetComment(const CStdString& comment)
{
  m_strComment = comment;
}

void CMusicInfoTag::SetLyrics(const CStdString& lyrics)
{
  m_strLyrics = lyrics;
}

void CMusicInfoTag::SetRating(char rating)
{
  m_rating = rating;
}

void CMusicInfoTag::SetListeners(int listeners)
{
 m_listeners = listeners;
}

void CMusicInfoTag::SetPlayCount(int playcount)
{
  m_iTimesPlayed = playcount;
}

void CMusicInfoTag::SetLastPlayed(const CStdString& lastplayed)
{
  m_strLastPlayed = lastplayed;
}

void CMusicInfoTag::SetLoaded(bool bOnOff)
{
  m_bLoaded = bOnOff;
}

bool CMusicInfoTag::Loaded() const
{
  return m_bLoaded;
}
// Laureon: Added BEGIN
const CStdString& CMusicInfoTag::GetLabel() const {
  return m_strLabel;
}

const CStdString& CMusicInfoTag::GetISRC() const {
  return m_strISRC;
}

void CMusicInfoTag::SetLabel(const CStdString& strLabel) {
  m_strLabel = Trim(strLabel);
}

void CMusicInfoTag::SetISRC(const CStdString& strISRC) {
  m_strISRC = Trim(strISRC);
}
// Laureon: Added END
void CMusicInfoTag::SetAlbum(const CAlbum& album)
{
  SetArtist(album.strArtist);
  SetAlbum(album.strAlbum);
  SetAlbumArtist(album.strArtist);
  SetGenre(album.strGenre);
  SetRating('0' + (album.iRating + 1) / 2);
  SYSTEMTIME stTime;
  stTime.wYear = album.iYear;
  SetReleaseDate(stTime);
  m_iDbId = album.idAlbum;
  m_bLoaded = true;
  SetArtistId(album.idArtist);
  SetAlbumId(album.idAlbum);
}

void CMusicInfoTag::SetSong(const CSong& song)
{
  SetISRC(song.strISRC); // Laureon: Added
  SetLabel(song.strLabel); // Laureon: Added
  SetTitle(song.strTitle);
  SetGenre(song.strGenre);
  SetArtist(song.strArtist);
  SetAlbum(song.strAlbum);
  SetAlbumArtist(song.strAlbumArtist);
  SetComment(song.strComment);
  SetPlayCount(song.iTimesPlayed);
  SetLastPlayed(song.lastPlayed);
  m_rating = song.rating;
  m_strURL = song.strFileName;
  SYSTEMTIME stTime;
  stTime.wYear = song.iYear;
  SetReleaseDate(stTime);
  m_iTrack = song.iTrack;
  m_iDuration = song.iDuration;
  m_iDbId = song.idSong;
  m_bLoaded = true;
  m_iTimesPlayed = song.iTimesPlayed;
  m_iArtistId = song.iArtistId;
  m_iAlbumId = song.iAlbumId;
}

void CMusicInfoTag::Serialize(CVariant& value)
{
  value["url"] = m_strURL;
  value["title"] = m_strTitle;
  value["artist"] = m_strArtist;
  value["album"] = m_strAlbum;
  value["albumartist"] = m_strAlbumArtist;
  value["genre"] = m_strGenre;
  value["duration"] = m_iDuration;
  value["track"] = m_iTrack;
  value["loaded"] = m_bLoaded;
  value["year"] = m_dwReleaseDate.wYear;
  value["comment"] = m_strComment;
  value["rating"] = m_rating;
  value["playcount"] = m_iTimesPlayed;
  value["lyrics"] = m_strLyrics;
  value["artistid"] = m_iArtistId;
  value["albumid"] = m_iAlbumId;
  value["ISRC"] = m_strISRC; // Laureon: Added
  value["label"] = m_strLabel; // Laureon: Added
}
void CMusicInfoTag::Archive(CArchive& ar)
{
  if (ar.IsStoring())
  {
    ar << m_strURL;
    ar << m_strTitle;
    ar << m_strArtist;
    ar << m_strAlbum;
    ar << m_strAlbumArtist;
    ar << m_strGenre;
    ar << m_iDuration;
    ar << m_iTrack;
    ar << m_bLoaded;
    ar << m_dwReleaseDate;
    ar << m_strLastPlayed;
    ar << m_strComment;
    ar << m_rating;
    ar << m_iTimesPlayed;
    ar << m_iArtistId;
    ar << m_iAlbumId;
    ar << m_strISRC; // Laureon: Added
    ar << m_strLabel; // Laureon: Added
  }
  else
  {
    ar >> m_strURL;
    ar >> m_strTitle;
    ar >> m_strArtist;
    ar >> m_strAlbum;
    ar >> m_strAlbumArtist;
    ar >> m_strGenre;
    ar >> m_iDuration;
    ar >> m_iTrack;
    ar >> m_bLoaded;
    ar >> m_dwReleaseDate;
    ar >> m_strLastPlayed;
    ar >> m_strComment;
    ar >> m_rating;
    ar >> m_iTimesPlayed;
    ar >> m_iArtistId;
    ar >> m_iAlbumId;
    ar >> m_strISRC; // Laureon: Added
    ar >> m_strLabel; // Laureon: Added
 }
}

void CMusicInfoTag::Clear()
{
  m_strURL.Empty();
  m_strArtist.Empty();
  m_strAlbum.Empty();
  m_strAlbumArtist.Empty();
  m_strGenre.Empty();
  m_strTitle.Empty();
  m_iDuration = 0;
  m_iTrack = 0;
  m_bLoaded = false;
  m_strLastPlayed.Empty();
  m_strComment.Empty();
  m_strLabel.Empty(); // Laureon: Added
  m_strISRC.Empty(); // Laureon: Added
  m_rating = '0';
  m_iDbId = -1;
  m_iTimesPlayed = 0;
  memset(&m_dwReleaseDate, 0, sizeof(m_dwReleaseDate) );
  m_iArtistId = -1;
  m_iAlbumId = -1;
}

void CMusicInfoTag::AppendArtist(const CStdString &artist)
{
  if (m_strArtist.IsEmpty())
    return SetArtist(artist);
  std::vector<CStdString> values;
  CStdString value(Trim(artist));
  StringUtils::SplitString(m_strArtist, g_advancedSettings.m_musicItemSeparator, values);
  if (std::find(values.begin(), values.end(), value) == values.end())
    m_strArtist += g_advancedSettings.m_musicItemSeparator + value;
}

void CMusicInfoTag::AppendAlbumArtist(const CStdString &albumArtist)
{
  if (m_strAlbumArtist.IsEmpty())
    return SetAlbumArtist(albumArtist);
  std::vector<CStdString> values;
  CStdString value(Trim(albumArtist));
  StringUtils::SplitString(m_strAlbumArtist, g_advancedSettings.m_musicItemSeparator, values);
  if (std::find(values.begin(), values.end(), value) == values.end())
    m_strAlbumArtist += g_advancedSettings.m_musicItemSeparator + value;
}

void CMusicInfoTag::AppendGenre(const CStdString &genre)
{
  if (m_strGenre.IsEmpty())
    return SetGenre(genre);
  std::vector<CStdString> values;
  CStdString value(Trim(genre));
  StringUtils::SplitString(m_strGenre, g_advancedSettings.m_musicItemSeparator, values);
  if (std::find(values.begin(), values.end(), value) == values.end())
    m_strGenre += g_advancedSettings.m_musicItemSeparator + value;
}

CStdString CMusicInfoTag::Trim(const CStdString &value) const
{
  CStdString trimmedValue(value);
  trimmedValue.TrimLeft(' ');
  trimmedValue.TrimRight(" \n\r");
  return trimmedValue;
}
