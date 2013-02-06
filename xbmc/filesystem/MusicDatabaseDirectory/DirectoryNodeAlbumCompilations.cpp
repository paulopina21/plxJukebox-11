

#include "DirectoryNodeAlbumCompilations.h"
#include "QueryParams.h"
#include "music/MusicDatabase.h"

using namespace XFILE::MUSICDATABASEDIRECTORY;

CDirectoryNodeAlbumCompilations::CDirectoryNodeAlbumCompilations(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_ALBUM_COMPILATIONS, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeAlbumCompilations::GetChildType() const
{
  if (GetName()=="-1")
    return NODE_TYPE_ALBUM_COMPILATIONS_SONGS;

  return NODE_TYPE_SONG;
}

CStdString CDirectoryNodeAlbumCompilations::GetLocalizedName() const
{
  if (GetID() == -1)
    return g_localizeStrings.Get(15102); // All Albums
  CMusicDatabase db;
  if (db.Open())
    return db.GetAlbumById(GetID());
  return "";
}

bool CDirectoryNodeAlbumCompilations::GetContent(CFileItemList& items) const
{
  CMusicDatabase musicdatabase;
  if (!musicdatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  bool bSuccess=musicdatabase.GetVariousArtistsAlbums(BuildPath(), items);

  musicdatabase.Close();

  return bSuccess;
}
