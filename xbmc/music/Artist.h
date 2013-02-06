#pragma once



#include <map>
#include <vector>

#include "utils/ScraperUrl.h"
#include "utils/Fanart.h"

class TiXmlNode;

class CArtist
{
public:
  long idArtist;
  bool operator<(const CArtist& a) const
  {
    return strArtist < a.strArtist;
  }

  void Reset()
  {
    strArtist.Empty();
    strGenre.Empty();
    strBiography.Empty();
    strStyles.Empty();
    strMoods.Empty();
    strInstruments.Empty();
    strBorn.Empty();
    strFormed.Empty();
    strDied.Empty();
    strDisbanded.Empty();
    strYearsActive.Empty();
    thumbURL.Clear();
    discography.clear();
    idArtist = -1;
  }

  /*! \brief Load artist information from an XML file.
   See CVideoInfoTag::Load for a description of the types of elements we load.
   \param element    the root XML element to parse.
   \param append     whether information should be added to the existing tag, or whether it should be reset first.
   \param prioritise if appending, whether additive tags should be prioritised (i.e. replace or prepend) over existing values. Defaults to false.
   \sa CVideoInfoTag::Load
   */
  bool Load(const TiXmlElement *element, bool append = false, bool prioritise = false);
  bool Save(TiXmlNode *node, const CStdString &tag, const CStdString& strPath);

  CStdString strArtist;
  CStdString strGenre;
  CStdString strBiography;
  CStdString strStyles;
  CStdString strMoods;
  CStdString strInstruments;
  CStdString strBorn;
  CStdString strFormed;
  CStdString strDied;
  CStdString strDisbanded;
  CStdString strYearsActive;
  CScraperUrl thumbURL;
  CFanart fanart;
  std::vector<std::pair<CStdString,CStdString> > discography;
};

typedef std::vector<CArtist> VECARTISTS;
