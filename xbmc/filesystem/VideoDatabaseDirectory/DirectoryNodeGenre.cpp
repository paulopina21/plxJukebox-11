

#include "DirectoryNodeGenre.h"
#include "QueryParams.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeGenre::CDirectoryNodeGenre(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_GENRE, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeGenre::GetChildType() const
{
  CQueryParams params;
  CollectQueryParams(params);
  if (params.GetContentType() == VIDEODB_CONTENT_MOVIES)
    return NODE_TYPE_TITLE_MOVIES;
  if (params.GetContentType() == VIDEODB_CONTENT_MUSICVIDEOS)
    return NODE_TYPE_TITLE_MUSICVIDEOS;

  return NODE_TYPE_TITLE_TVSHOWS;
}

CStdString CDirectoryNodeGenre::GetLocalizedName() const
{
  CVideoDatabase db;
  if (db.Open())
    return db.GetGenreById(GetID());
  return "";
}

bool CDirectoryNodeGenre::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  bool bSuccess=videodatabase.GetGenresNav(BuildPath(), items, params.GetContentType());

  videodatabase.Close();

  return bSuccess;
}
