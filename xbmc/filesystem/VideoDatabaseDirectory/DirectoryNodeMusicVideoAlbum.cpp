

#include "DirectoryNodeMusicVideoAlbum.h"
#include "QueryParams.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeMusicVideoAlbum::CDirectoryNodeMusicVideoAlbum(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_MUSICVIDEOS_ALBUM, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeMusicVideoAlbum::GetChildType() const
{
  return NODE_TYPE_TITLE_MUSICVIDEOS;
}

CStdString CDirectoryNodeMusicVideoAlbum::GetLocalizedName() const
{
  CVideoDatabase db;
  if (db.Open())
    return db.GetMusicVideoAlbumById(GetID());
  return "";
}

bool CDirectoryNodeMusicVideoAlbum::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  bool bSuccess=videodatabase.GetMusicVideoAlbumsNav(BuildPath(), items, params.GetActorId());

  videodatabase.Close();

  return bSuccess;
}

