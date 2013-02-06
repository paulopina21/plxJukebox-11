

#include "DirectoryNodeYearAlbum.h"
#include "QueryParams.h"
#include "music/MusicDatabase.h"

using namespace XFILE::MUSICDATABASEDIRECTORY;

CDirectoryNodeYearAlbum::CDirectoryNodeYearAlbum(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_YEAR_ALBUM, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeYearAlbum::GetChildType() const
{
  if (GetName()=="-1")
    return NODE_TYPE_YEAR_SONG;

  return NODE_TYPE_SONG;
}

CStdString CDirectoryNodeYearAlbum::GetLocalizedName() const
{
  if (GetID() == -1)
    return g_localizeStrings.Get(15102); // All Albums
  CMusicDatabase db;
  if (db.Open())
    return db.GetAlbumById(GetID());
  return "";
}

bool CDirectoryNodeYearAlbum::GetContent(CFileItemList& items) const
{
  CMusicDatabase musicdatabase;
  if (!musicdatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  bool bSuccess=musicdatabase.GetAlbumsByYear(BuildPath(), items, params.GetYear());

  musicdatabase.Close();

  return bSuccess;
}
