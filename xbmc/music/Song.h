
/*!
 \file Song.h
\brief
*/
#pragma once

#include "utils/StringUtils.h"
#include "utils/ISerializable.h"
#include "utils/XMLUtils.h" // Laureon: Added to save and load methods

#include <map>
#include <vector>

namespace MUSIC_INFO
{
  class CMusicInfoTag;
}

/*!
 \ingroup music
 \brief Class to store and read album information from CMusicDatabase
 \sa CSong, CMusicDatabase
 */

class CGenre
{
public:
  long idGenre;
  CStdString strGenre;
};

/*!
 \ingroup music
 \brief Class to store and read song information from CMusicDatabase
 \sa CAlbum, CMusicDatabase
 */
class CSong: public ISerializable
{
public:
  CSong() ;
  CSong(MUSIC_INFO::CMusicInfoTag& tag);
  virtual ~CSong(){};
  void Clear() ;
  virtual void Serialize(CVariant& value);

  bool Load(const TiXmlElement *songElement, bool append = false);

//  bool Load(const TiXmlElement *movie, bool chained=false); // Laureon: TODO: Get this thing off Album.cpp and implement in here!!
  bool Save(TiXmlNode *node, const CStdString &tag, const CStdString& strPath); // Laureon: Added


  bool operator<(const CSong &song) const
  {
    if (strFileName < song.strFileName) return true;
    if (strFileName > song.strFileName) return false;
    if (iTrack < song.iTrack) return true;
    return false;
  }
  long idSong;
  CStdString strISRC; // Laureon: Added ISRC
  CStdString strFileName;
  CStdString strTitle;
  CStdString strArtist;
  CStdString strAlbum;
  CStdString strAlbumArtist;
  CStdString strGenre;
  CStdString strThumb;
  CStdString strComment;
  CStdString strLabel; // Laureon: Added Studio Label

  int iVisible;

  char rating;
  int iTrack;
  int iDuration;
  int iYear;
  int iTimesPlayed;
  CStdString lastPlayed;
  int iStartOffset;
  int iEndOffset;
  int iArtistId;
  int iAlbumId;

  // Karaoke-specific information
  long       iKaraokeNumber;        //! Karaoke song number to "select by number". 0 for non-karaoke
  CStdString strKaraokeLyrEncoding; //! Karaoke song lyrics encoding if known. Empty if unknown.
  int        iKaraokeDelay;         //! Karaoke song lyrics-music delay in 1/10 seconds.
};

/*!
 \ingroup music
 \brief A map of CSong objects, used for CMusicDatabase
 */
class CSongMap
{
public:
  CSongMap();

  std::map<CStdString, CSong>::const_iterator Begin();
  std::map<CStdString, CSong>::const_iterator End();
  CSong *Find(const CStdString &file);
  void Add(const CStdString &file, const CSong &song);
  void Clear();
  int Size();

private:
  std::map<CStdString, CSong> m_map;
};

/*!
 \ingroup music
 \brief A vector of CSong objects, used for CMusicDatabase
 \sa CMusicDatabase
 */
typedef std::vector<CSong> VECSONGS;

/*!
 \ingroup music
 \brief A vector of CStdString objects, used for CMusicDatabase
 \sa CMusicDatabase
 */
typedef std::vector<CGenre> VECGENRES;
