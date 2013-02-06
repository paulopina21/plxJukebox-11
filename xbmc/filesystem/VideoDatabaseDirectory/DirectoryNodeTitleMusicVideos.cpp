

#include "DirectoryNodeTitleMusicVideos.h"
#include "QueryParams.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeTitleMusicVideos::CDirectoryNodeTitleMusicVideos(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_TITLE_MUSICVIDEOS, strName, pParent)
{

}

bool CDirectoryNodeTitleMusicVideos::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  CStdString strBaseDir=BuildPath();
  bool bSuccess=videodatabase.GetMusicVideosNav(strBaseDir, items, params.GetGenreId(), params.GetYear(), params.GetActorId(), params.GetDirectorId(),params.GetStudioId(),params.GetAlbumId());

  videodatabase.Close();

  return bSuccess;
}
