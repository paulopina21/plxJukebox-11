

#include "DirectoryNodeTitleMovies.h"
#include "QueryParams.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeTitleMovies::CDirectoryNodeTitleMovies(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_TITLE_MOVIES, strName, pParent)
{

}

bool CDirectoryNodeTitleMovies::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  CStdString strBaseDir=BuildPath();
  bool bSuccess=videodatabase.GetMoviesNav(strBaseDir, items, params.GetGenreId(), params.GetYear(), params.GetActorId(), params.GetDirectorId(), params.GetStudioId(), params.GetCountryId(), params.GetSetId());

  videodatabase.Close();

  return bSuccess;
}
