

#include "DirectoryNodeTitleTvShows.h"
#include "QueryParams.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeTitleTvShows::CDirectoryNodeTitleTvShows(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_TITLE_TVSHOWS, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeTitleTvShows::GetChildType() const
{
  return NODE_TYPE_SEASONS;
}

CStdString CDirectoryNodeTitleTvShows::GetLocalizedName() const
{
  CVideoDatabase db;
  if (db.Open())
    return db.GetTvShowTitleById(GetID());
  return "";
}

bool CDirectoryNodeTitleTvShows::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  bool bSuccess=videodatabase.GetTvShowsNav(BuildPath(), items, params.GetGenreId(), params.GetYear(), params.GetActorId(), params.GetDirectorId(), params.GetStudioId());

  videodatabase.Close();

  return bSuccess;
}
