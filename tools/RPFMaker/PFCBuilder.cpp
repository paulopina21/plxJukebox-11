#include <string.h>
#include <plxfw/includes/utils/Files.h>
#include <plxfw/includes/utils/StringUtils.h>
#include "PFCBuilder.h"

using namespace plxfw::utils;
using namespace plxfw::filesystem;

using namespace std;

int s_atoi(const char* str)
{
	if (!str || strcmp(str, "") == 0) return 0;
	return atoi(str);
}

double s_atof(const char* str)
{
	if (!str || strcmp(str, "") == 0) return 0.0f;
	return atof(str);
}

sFileToInsert make_insert(const CStdString& strFileName, const CStdString& strInternalFileName, eENTRYTYPE	eType) {
	sFileToInsert insert;
	insert.strFileName = strFileName;
	insert.strInternalFileName = strInternalFileName;
	insert.eType = eType;

	return insert;
}

bool CPFCBuilder::CreateFromFile(CStdString contentxml, const char * strOutPath)
{

	TiXmlDocument xmlDocument;

	if (!plx_file_exists(contentxml.c_str()))
	{ // tell the user it doesn't exist
		cout << " Input file not found: " << contentxml.c_str() << "\n";
		return false;
	}

	if (!xmlDocument.LoadFile(contentxml))
	{
		cout << " Error loading: " << contentxml.c_str() << "\n";
		cout << " Line: " << xmlDocument.ErrorRow() << "\n";
		cout << " Error: " << xmlDocument.ErrorDesc() << "\n";
		return false;
	}

	TiXmlElement *pRootElement = xmlDocument.RootElement();

	if (pRootElement && strcasecmp(pRootElement->Value(), RPF_PACK_DEF_FILE_HEADER) != 0)
	{
		cout << "Error loading: " << contentxml.c_str() << " no <RPF_FILE_SYSTEM> node \n";
		return false;
	}

	m_RPFType = s_atoi(pRootElement->Attribute("TYPE"));
	m_RPFVersion = (float) s_atof(pRootElement->Attribute("VER"));

	switch (m_RPFType) {
		case RPF_PACK_TYPE_NONE:
			return false;
		break;
		case RPF_PACK_TYPE_PACKAGE:
			return false;
		break;
		case RPF_PACK_TYPE_ALBUM:
			return BuildAlbumPack(pRootElement, strOutPath);
		break;
		case RPF_PACK_TYPE_MOVIE:
			return false;
		break;
		case RPF_PACK_TYPE_TVSHOW:
			return false;
		break;
		case RPF_PACK_TYPE_ECLASS:
			return false;
		break;
	}
	return false;
	// succeeded - tell the user it worked
	//CLog::Log(LOGNOTICE, "Loaded advancedsettings.xml from %s", contentxml.c_str());
}

bool CPFCBuilder::BuildAlbumPack(TiXmlElement *pRootElement, const char * strOutPath)
{
	FeedArtistsInfo(pRootElement);

	// Artists
	for (VECARTISTS::iterator itArtist = m_artists.begin(); itArtist != m_artists.end(); ++itArtist)
	{
		if (itArtist->m_albums.size() <= 0) continue;

		VECINSERTFILES filestoadd; // Laureon: this is <realfilename, internalfilename>

		CStdString InternalFanartName = "fanart";
		InternalFanartName.append(StringUtils::GetExtension(itArtist->strFanart));
		filestoadd.push_back(make_insert(itArtist->strFanart, InternalFanartName, RPF_ENTRY_TYPE_FILE_HIDDEN));
		itArtist->strFanart = InternalFanartName;

		// Albums
		for (VECALBUMS::iterator itAlbum = itArtist->m_albums.begin(); itAlbum != itArtist->m_albums.end(); ++itAlbum)
		{
			if (itAlbum->songs.size() <= 0) continue;

			CStdString InternalCoverFile = "cover";
			InternalCoverFile.append(StringUtils::GetExtension(itAlbum->thumbURL));
			filestoadd.push_back(make_insert(itAlbum->thumbURL, InternalCoverFile, RPF_ENTRY_TYPE_FILE_HIDDEN));
			itAlbum->thumbURL = InternalCoverFile;

			// Songs
			for (std::vector<CSong>::iterator itSong = itAlbum->songs.begin(); itSong != itAlbum->songs.end(); ++itSong)
			{
				CStdString strSongfileName(itSong->strFileName);
				CStdString strInternalName;

				if (!itSong->strISRC.IsEmpty())
				{
					strInternalName = itSong->strISRC;
					strInternalName.append(StringUtils::GetExtension(itSong->strFileName));
				}
				else
					strInternalName = StringUtils::GetFileName(itSong->strFileName);

				filestoadd.push_back(make_insert(itSong->strFileName, strInternalName, RPF_ENTRY_TYPE_FILE));

				itSong->strFileName = strInternalName;
			}

			CStdString strTempFile;
			strTempFile.append(strOutPath);
			strTempFile.append("defs.tmp");
			remove(strTempFile.c_str()); // Just to be sure it doesn't exists...

			if (itArtist->SaveToFile(strTempFile, RPF_PACK_DEF_FILE_HEADER))
				filestoadd.push_back(make_insert(strTempFile, "defs.nfo", RPF_ENTRY_TYPE_SYSTEM));

			// Laureon: Work the filename
			CStdString strFilename;
			strFilename.append(strOutPath);
			strFilename.append(itArtist->strArtist);
			strFilename.append(" - ");
			strFilename.append(itAlbum->strAlbum);
			strFilename.append(".pfc");

			// Laureon: Create the pak file
			CFilePFC *RPCFile = new CFilePFC();
			RPCFile->Open(strFilename, true, RPF_PACK_TYPE_ALBUM);

			for (VECINSERTFILES::iterator itFiles = filestoadd.begin(); itFiles != filestoadd.end(); ++itFiles) {
				RPCFile->InsertFile(itFiles->strFileName, itFiles->strInternalFileName, itFiles->eType);
			}

			remove(strTempFile.c_str());
			delete RPCFile;

		}

	}

	return true;
}

bool CPFCBuilder::FeedArtistsInfo(TiXmlElement *pRootElement /*= 0*/)
{
	if (!pRootElement) return false;

	m_artists.clear();

	for (TiXmlNode* node = pRootElement->FirstChild("artist"); node; node = node->NextSibling("artist"))
	{
		TiXmlElement* pArtistElement = node->ToElement();

		if (!pArtistElement) return false;

		CArtist Artist;
		Artist.Load(pArtistElement);

		m_artists.push_back(Artist);
	}

	return true;
}

//bool CPFCBuilder::FeedAlbumsInfo(TiXmlElement *pRootElement)
//{
//	if (!pRootElement) return false;
//
//	for (TiXmlNode* node = pRootElement->FirstChild("album"); node; node = node->NextSibling("album"))
//	{
//		TiXmlElement* pAlbumElement = node->ToElement();
//		if (!pAlbumElement) return false;
//
//		CAlbum Album;
//
//		Album.Load(pAlbumElement);
//
//		m_albuns.push_back(Album);
//	}
//
//	return true;
//}

//bool RPFBuilder::FeedSongsInfo(sAlbum* Album, TiXmlElement *pAlbumElement) {
//      if (!pAlbumElement) return false;
//
//      Album->Songs.clear();
//
//      for(TiXmlNode* node = pAlbumElement->FirstChild("track"); node; node = node->NextSibling("track")) {
//              sSong Song;
//              TiXmlElement* pTrackElement = node->ToElement();
//
//              if (!pTrackElement) return false;
//
//              Song.ISRC               = s_GetText(pTrackElement,"ISRC");
//              Song.Track      = s_atoi(s_GetText(pTrackElement,"position"));
//              Song.strTitle   = s_GetText(pTrackElement,"title");
//              Song.Artist = s_GetText(pTrackElement,"artist");
//              Song.Label      = s_GetText(pTrackElement,"label");
//              Song.AlbumTitle = s_GetText(pTrackElement,"album");
//              Song.strPath = s_GetText(pTrackElement,"path");
//
//              Song.Time               = s_atoi(s_GetText(pTrackElement,"time"));
//
//
//              // Data check
//              if (Song.AlbumTitle.IsEmpty()) Song.AlbumTitle = Album->Title;
//              if (Song.Artist.IsEmpty()) Song.Artist = Album->AlbumArtist;
//              if (Song.Label.IsEmpty()) Song.Label = Album->Label;
//
//              //if (!ValidateSong(Song)) continue;
//
//              if (Song.strTitle.IsEmpty()) {
//                      Song.strTitle = plx_file_getFileName(Song.strPath);
//                      //plx_file_removeExt(Song.Title);
//              }
//
//              Song.bABLF = (Song.ISRC != ""); //TODO: Validate ISRC
//
//              Album->Songs.push_back(Song);
//      }
//      return true;
//}

bool CPFCBuilder::ValidateSong(CSong *Song)
{
	if (!plx_file_exists(Song->strFileName)) return false;

	if (Song->strAlbumArtist.IsEmpty()) return false;
	return true;
	//if (Song.Label.IsEmpty()) return false; // to validate ablf
}

