

#include "DirectoryNodeGenre.h"
#include "QueryParams.h"
#include "music/MusicDatabase.h"

using namespace XFILE::MUSICDATABASEDIRECTORY;

CDirectoryNodeGenre::CDirectoryNodeGenre(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_GENRE, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeGenre::GetChildType() const
{
  return NODE_TYPE_ARTIST;
}

CStdString CDirectoryNodeGenre::GetLocalizedName() const
{
  CMusicDatabase db;
  if (db.Open())
    return db.GetGenreById(GetID());
  return "";
}

bool CDirectoryNodeGenre::GetContent(CFileItemList& items) const
{
  CMusicDatabase musicdatabase;
  if (!musicdatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  bool bSuccess=musicdatabase.GetGenresNav(BuildPath(), items);

  musicdatabase.Close();

  return bSuccess;
}
