

#include "DirectoryNodeStudio.h"
#include "QueryParams.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeStudio::CDirectoryNodeStudio(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_STUDIO, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeStudio::GetChildType() const
{
  CQueryParams params;
  CollectQueryParams(params);
  if (params.GetContentType() == VIDEODB_CONTENT_MOVIES)
    return NODE_TYPE_TITLE_MOVIES;
  if (params.GetContentType() == VIDEODB_CONTENT_MUSICVIDEOS)
    return NODE_TYPE_TITLE_MUSICVIDEOS;

  return NODE_TYPE_TITLE_TVSHOWS;
}

CStdString CDirectoryNodeStudio::GetLocalizedName() const
{
  CVideoDatabase db;
  if (db.Open())
    return db.GetStudioById(GetID());
  return "";
}

bool CDirectoryNodeStudio::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  bool bSuccess=videodatabase.GetStudiosNav(BuildPath(), items, params.GetContentType());

  videodatabase.Close();

  return bSuccess;
}
