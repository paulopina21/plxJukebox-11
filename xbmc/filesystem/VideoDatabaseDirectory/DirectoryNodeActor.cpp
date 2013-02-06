

#include "DirectoryNodeActor.h"
#include "QueryParams.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeActor::CDirectoryNodeActor(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_ACTOR, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeActor::GetChildType() const
{
  CQueryParams params;
  CollectQueryParams(params);
  if (params.GetContentType() == VIDEODB_CONTENT_MOVIES)
    return NODE_TYPE_TITLE_MOVIES;
  if (params.GetContentType() == VIDEODB_CONTENT_MUSICVIDEOS)
    return NODE_TYPE_MUSICVIDEOS_ALBUM;

  return NODE_TYPE_TITLE_TVSHOWS;
}

CStdString CDirectoryNodeActor::GetLocalizedName() const
{
  CVideoDatabase db;
  if (db.Open())
    return db.GetPersonById(GetID());
  return "";
}

bool CDirectoryNodeActor::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  bool bSuccess=videodatabase.GetActorsNav(BuildPath(), items, params.GetContentType());

  videodatabase.Close();

  return bSuccess;
}

