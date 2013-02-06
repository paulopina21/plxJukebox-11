#include "Song.h"
#include "music/tags/MusicInfoTag.h"
#include "utils/Variant.h"

using namespace std;
using namespace MUSIC_INFO;

CSong::CSong(CMusicInfoTag& tag)
{
  SYSTEMTIME stTime;
  tag.GetReleaseDate(stTime);
  strTitle = tag.GetTitle();
  strGenre = tag.GetGenre();
  strFileName = tag.GetURL();
  strArtist = tag.GetArtist();
  strAlbum = tag.GetAlbum();
  strAlbumArtist = tag.GetAlbumArtist();
  strComment = tag.GetComment();
  strLabel = tag.GetLabel(); // Laureon: Added getLabel 
  strISRC = tag.GetISRC(); // Laureon: Added getISRC
  iVisible = 1; // Laureon: Added: Song Visibility
  rating = tag.GetRating();
  iYear = stTime.wYear;
  iTrack = tag.GetTrackAndDiskNumber();
  iDuration = tag.GetDuration();
  strThumb = "";
  iStartOffset = 0;
  iEndOffset = 0;
  idSong = -1;
  iTimesPlayed = 0;
  iKaraokeNumber = 0;
  iKaraokeDelay = 0;         //! Karaoke song lyrics-music delay in 1/10 seconds.
  iArtistId = -1;
  iAlbumId = -1;
}

CSong::CSong()
{
  Clear();
}

void CSong::Serialize(CVariant& value)
{
  value["filename"] = strFileName;
  value["title"] = strTitle;
  value["artist"] = strArtist;
  value["album"] = strAlbum;
  value["albumartist"] = strAlbumArtist;
  value["genre"] = strGenre;
  value["duration"] = iDuration;
  value["track"] = iTrack;
  value["year"] = iYear;
  value["comment"] = strComment;
  value["rating"] = rating;
  value["timesplayed"] = iTimesPlayed;
  value["karaokenumber"] = (int64_t) iKaraokeNumber;
  value["artistid"] = iArtistId;
  value["albumid"] = iAlbumId;
  value["ISRC"] = strISRC; // Laureon: Added
  value["label"] = strLabel; // Laureon: Added
}

void CSong::Clear()
{
  strFileName.Empty();
  strTitle.Empty();
  strArtist.Empty();
  strAlbum.Empty();
  strAlbumArtist.Empty();
  strGenre.Empty();
  strThumb.Empty();
  strISRC.Empty(); // Laureon: Added
  strLabel.Empty(); // Laureon: Added
  strComment.Empty();
  iVisible = 1; // Laureon: Added: Song Visibility
  rating = '0';
  iTrack = 0;
  iDuration = 0;
  iYear = 0;
  iStartOffset = 0;
  iEndOffset = 0;
  idSong = -1;
  iTimesPlayed = 0;
  lastPlayed = "";
  iKaraokeNumber = 0;
  strKaraokeLyrEncoding.Empty();
  iKaraokeDelay = 0;
  iArtistId = -1;
  iAlbumId = -1;
}

bool CSong::Load(const TiXmlElement *songElement, bool append)
{
  if (!songElement) return false;
  if (!append)
    Clear();

  XMLUtils::GetInt(songElement,"position",iTrack);

  bool bIncrement = false;

  if (iTrack == 0)
    bIncrement = true;

  XMLUtils::GetString(songElement,"title",strTitle);
  CStdString strDur;
  //XMLUtils::GetString(songElement,"duration",strDur);
  //iDuration = StringUtils::TimeStringToSeconds(strDur);
  XMLUtils::GetInt(songElement, "duration", iDuration); // Laureon: Always in seconds...

  if (bIncrement)
    iTrack = iTrack + 1;

  // Laureon: Jukebox Songs Info System for ABLF
  XMLUtils::GetString(songElement,"ISRC",strISRC);
  XMLUtils::GetString(songElement,"artist",strArtist);
  XMLUtils::GetString(songElement, "album", strAlbum);
  XMLUtils::GetString(songElement, "label", strLabel);
  XMLUtils::GetString(songElement, "path", strFileName);
  // Laureon: END BLOCK
  return true;
}

bool CSong::Save(TiXmlNode *node, const CStdString &tag, const CStdString& strPath) {
  if (!node) return false;

  TiXmlElement trackElement(tag.c_str());
  TiXmlNode* trackNode = node->InsertEndChild(trackElement);

  XMLUtils::SetString(trackNode, "ISRC", this->strISRC);
  XMLUtils::SetInt(trackNode, "position", this->iTrack);
  XMLUtils::SetString(trackNode, "title", this->strTitle);
  XMLUtils::SetInt(trackNode, "duration", this->iDuration);
  XMLUtils::SetString(trackNode, "artist",this->strArtist);
  XMLUtils::SetString(trackNode, "album", this->strAlbum);
  XMLUtils::SetString(trackNode, "label", this->strLabel);
  XMLUtils::SetString(trackNode, "path", this->strFileName);
  //		TiXmlText name3(StringUtils::SecondsToTimeString(it->iDuration)); Laureon: TODO: Reimplement the "iDuration code"...
}


CSongMap::CSongMap()
{
}

std::map<CStdString, CSong>::const_iterator CSongMap::Begin()
{
  return m_map.begin();
}

std::map<CStdString, CSong>::const_iterator CSongMap::End()
{
  return m_map.end();
}

void CSongMap::Add(const CStdString &file, const CSong &song)
{
  CStdString lower = file;
  lower.ToLower();
  m_map.insert(pair<CStdString, CSong>(lower, song));
}

CSong* CSongMap::Find(const CStdString &file)
{
  CStdString lower = file;
  lower.ToLower();
  map<CStdString, CSong>::iterator it = m_map.find(lower);
  if (it == m_map.end())
    return NULL;
  return &(*it).second;
}

void CSongMap::Clear()
{
  m_map.erase(m_map.begin(), m_map.end());
}

int CSongMap::Size()
{
  return (int)m_map.size();
}

