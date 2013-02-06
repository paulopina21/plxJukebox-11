/*!
 \file Album.h
\brief
*/
#pragma once



#include <map>
#include <vector>

#include "Song.h"
#include "utils/ScraperUrl.h" // Laureon: No need for this anymore

class TiXmlNode;

class CAlbum
{
public:
  CAlbum() { idAlbum = 0; iRating = 0; iYear = 0; idArtist = 0; iVisible = -1; idPFCFile = -1;};
  bool operator<(const CAlbum &a) const
  {
    return strAlbum + strArtist < a.strAlbum + a.strArtist;
  }

  void Reset()
  {
    idAlbum = -1;
    iVisible = 1;
    idPFCFile = -1;
    strPFCFile.Empty(); // Laureon: Added: For better jukebox control
    strAlbum.Empty();
    strArtist.Empty();
    strGenre.Empty();
    thumbURL.Clear(); // Laureon: Modified to Empty. Was Clear
    strMoods.Empty();
    strStyles.Empty();
    strThemes.Empty();
    strReview.Empty();
    strLabel.Empty();
    strType.Empty();
    strGTIN.Empty(); // Laureon: GTIN for album identification
    m_strDateOfRelease.Empty();
    iRating=-1;
    iYear=-1;
    idArtist = -1;
    songs.clear();
  }

  /*! \brief Load album information from an XML file.
   See CVideoInfoTag::Load for a description of the types of elements we load.
   \param element    the root XML element to parse.
   \param append     whether information should be added to the existing tag, or whether it should be reset first.
   \param prioritise if appending, whether additive tags should be prioritised (i.e. replace or prepend) over existing values. Defaults to false.
   \sa CVideoInfoTag::Load
   */
  bool Load(const TiXmlElement *element, bool append = false, bool prioritise = false);
  bool Save(TiXmlNode *node, const CStdString &tag, const CStdString& strPath);

  long idAlbum;
  int iVisible;
  int idPFCFile; // Laureon: Added: For better jukebox control
  CStdString strPFCFile; // Laureon: Added: For better jukebox control
  CStdString strAlbum;
  CStdString strArtist;
  CStdString strGenre;
  CScraperUrl thumbURL; // Laureon: Was CScraperUrl
  CStdString strMoods;
  CStdString strStyles;
  CStdString strThemes;
  CStdString strReview;
  CStdString strLabel;
  CStdString strType;
  CStdString m_strDateOfRelease;
  CStdString strGTIN; // Laureon: Added GTIN
  
  int iRating;
  int iYear;
  int idArtist;
  VECSONGS songs;
};

typedef std::vector<CAlbum> VECALBUMS;
