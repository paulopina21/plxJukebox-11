

#include "DirectoryNodeAlbum.h"
#include "QueryParams.h"
#include "music/MusicDatabase.h"

using namespace XFILE::MUSICDATABASEDIRECTORY;

CDirectoryNodeAlbum::CDirectoryNodeAlbum(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_ALBUM, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeAlbum::GetChildType() const
{
  return NODE_TYPE_SONG;
}

CStdString CDirectoryNodeAlbum::GetLocalizedName() const
{
  if (GetID() == -1)
    return g_localizeStrings.Get(15102); // All Albums
  CMusicDatabase db;
  if (db.Open())
    return db.GetAlbumById(GetID());
  return "";
}

bool CDirectoryNodeAlbum::GetContent(CFileItemList& items) const
{
  CMusicDatabase musicdatabase;
  if (!musicdatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  bool bSuccess=musicdatabase.GetAlbumsNav(BuildPath(), items, params.GetGenreId(), params.GetArtistId(),-1,-1);

  musicdatabase.Close();

  return bSuccess;
}
