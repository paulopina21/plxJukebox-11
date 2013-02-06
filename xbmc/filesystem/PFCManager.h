#ifndef PFC_MANAGER_H
#define PFC_MANAGER_H

#include  "utils/StdString.h"

#include <memory.h>
#include <vector>
#include <map>
#include "File.h"
#include "../jukebox/PFCHeaders.h"
#include "../music/Album.h"
#include "../music/Artist.h"

using namespace XFILE;
using namespace std;

struct sFileMap {
	CStdString		      strPFCFileName;
	sRPFHeader		    sHeader;
	int64_t				        st_modtime;
	bool                  bLock;
	VECFILEENTRY	  vecFiles;

  sFileMap()
  {
    strPFCFileName = "";
    st_modtime = 0;
    bLock = false;
    vecFiles.clear();
  }

  sFileMap(const sFileMap& SNewItem)
  {
    memcpy(&bLock, &SNewItem.bLock, sizeof(bool));
    //memcpy(&strPFCFileName, &SNewItem.strPFCFileName, sizeof(CStdString));
    memcpy(&st_modtime, &SNewItem.st_modtime, sizeof(int64_t));
    //memcpy(&vecFiles, &SNewItem.vecFiles, sizeof(VECFILEENTRY));
  }

};

typedef std::vector<sFileMap> VECPFCFILESMAP;

class CPFCManager {
public:
	CPFCManager();
	~CPFCManager();

	bool Open(const CStdString& strFile, sRPFHeader& RPFHeader);

	ePACKTYPE GetPFCType(const CStdString& strPath);

	bool GetEntriesList(const CStdString& strPath, VECFILEENTRY& items);
	bool GetFileEntry(const CStdString& strPath, sFileEntry& item);

	CAlbum GetAlbumInfo(const CStdString& strPath);
	CArtist GetArtistInfo(const CStdString& strPath);

	bool ExtractArchive(const CStdString& strArchive, const CStdString& strPath);
	void CleanUp(const CStdString& strArchive, const CStdString& strPath); // deletes extracted archive. use with care!
	void release(const CStdString& strPath); // release resources used by PFC Listing Cache

	bool GetDefsFile(const CStdString& strPath,	TiXmlDocument& xmlDocument);
private:
	CFile m_actualFile;

	//sRPFHeader m_fileHeader;
	//sFileEntry*	m_sfiletable;

	VECPFCFILESMAP m_filesCache;

	inline bool CheckSign(sRPFHeader& RPFHeader);

	bool GetFromCache(const CStdString& strFile, sFileMap& item, bool bAutoCache = false);
	bool AppendToCache(const CStdString& strFile, sFileMap& item);
	bool IsCached(const CStdString& strFile);
};

extern CPFCManager g_PFCManager;

#endif
