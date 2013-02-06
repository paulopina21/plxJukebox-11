

#include "DirectoryNodeArtist.h"
#include "QueryParams.h"
#include "music/MusicDatabase.h"
#include "settings/GUISettings.h"

using namespace XFILE::MUSICDATABASEDIRECTORY;

CDirectoryNodeArtist::CDirectoryNodeArtist(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_ARTIST, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeArtist::GetChildType() const
{
  return NODE_TYPE_ALBUM;
}

CStdString CDirectoryNodeArtist::GetLocalizedName() const
{
  if (GetID() == -1)
    return g_localizeStrings.Get(15103); // All Artists
  CMusicDatabase db;
  if (db.Open())
    return db.GetArtistById(GetID());
  return "";
}

bool CDirectoryNodeArtist::GetContent(CFileItemList& items) const
{
  CMusicDatabase musicdatabase;
  if (!musicdatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  bool bSuccess = musicdatabase.GetArtistsNav(BuildPath(), items, params.GetGenreId(), !g_guiSettings.GetBool("musiclibrary.showcompilationartists"));

  musicdatabase.Close();

  return bSuccess;
}
