

#include "DirectoryNodeEpisodes.h"
#include "QueryParams.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeEpisodes::CDirectoryNodeEpisodes(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_EPISODES, strName, pParent)
{

}

bool CDirectoryNodeEpisodes::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  CStdString strBaseDir=BuildPath();

  int season = (int)params.GetSeason();
  if (season == -2)
    season = -1;

  bool bSuccess=videodatabase.GetEpisodesNav(strBaseDir, items, params.GetGenreId(), params.GetYear(), params.GetActorId(), params.GetDirectorId(), params.GetTvShowId(), season);

  videodatabase.Close();

  return bSuccess;
}
