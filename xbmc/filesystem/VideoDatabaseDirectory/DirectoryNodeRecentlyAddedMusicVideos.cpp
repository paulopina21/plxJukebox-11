

#include "DirectoryNodeRecentlyAddedMusicVideos.h"
#include "QueryParams.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeRecentlyAddedMusicVideos::CDirectoryNodeRecentlyAddedMusicVideos(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_RECENTLY_ADDED_MUSICVIDEOS, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeRecentlyAddedMusicVideos::GetChildType() const
{
  return NODE_TYPE_TITLE_MUSICVIDEOS;
}

bool CDirectoryNodeRecentlyAddedMusicVideos::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CStdString strBaseDir=BuildPath();
  bool bSuccess=videodatabase.GetRecentlyAddedMusicVideosNav(strBaseDir, items);

  videodatabase.Close();

  return bSuccess;
}

