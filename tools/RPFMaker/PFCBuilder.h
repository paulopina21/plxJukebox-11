#ifndef CPFCMANAGER_H
#define CPFCMANAGER_H

#include <plxfw/includes/music/Artist.h>
#include <plxfw/includes/music/Album.h>

#include <plxfw/includes/utils/StdString.h>
#include <plxfw/includes/utils/XMLUtils.h>
#include <plxfw/includes/filesystem/PFCHeaders.h>
#include <plxfw/includes/filesystem/CFilePFC.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

#define RPF_PACK_DEF_FILE_HEADER "RPF_FILE_SYSTEM"

struct sFileToInsert{
	CStdString	strFileName;
	CStdString	strInternalFileName;
	eENTRYTYPE	eType;
};

typedef std::vector<sFileToInsert> VECINSERTFILES;

sFileToInsert make_insert(const CStdString& strFileName, const CStdString& strInternalFileName, eENTRYTYPE eType = RPF_ENTRY_TYPE_FILE);

class CPFCBuilder {
public:
  bool CreateFromFile(CStdString contentxml,const char * strOutPath);

private:
  std::vector<CArtist> m_artists;
//  std::vector<CAlbum> m_albuns;
  CStdString Outfile;

  int   m_RPFType; // Reads a ePACKTYPE
  float	m_RPFVersion;

  bool BuildAlbumPack(TiXmlElement *pRootElement, const char * strOutPath);
  bool FeedArtistsInfo(TiXmlElement *pRootElement = 0);
//  bool FeedAlbumsInfo(TiXmlElement *pRootElement = 0);
  //bool FeedSongsInfo(CAlbum* Album, TiXmlElement *pAlbumElement = 0);
  bool ValidateSong(CSong *Song);

};

#endif
