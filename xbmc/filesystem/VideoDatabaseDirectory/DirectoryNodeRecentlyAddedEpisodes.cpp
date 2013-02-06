

#include "DirectoryNodeRecentlyAddedEpisodes.h"
#include "QueryParams.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeRecentlyAddedEpisodes::CDirectoryNodeRecentlyAddedEpisodes(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_RECENTLY_ADDED_EPISODES, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeRecentlyAddedEpisodes::GetChildType() const
{
  return NODE_TYPE_EPISODES;
}

bool CDirectoryNodeRecentlyAddedEpisodes::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CStdString strBaseDir=BuildPath();
  bool bSuccess=videodatabase.GetRecentlyAddedEpisodesNav(strBaseDir, items);

  videodatabase.Close();

  return bSuccess;
}
