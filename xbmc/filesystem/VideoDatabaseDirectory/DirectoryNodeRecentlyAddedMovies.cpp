

#include "DirectoryNodeRecentlyAddedMovies.h"
#include "QueryParams.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeRecentlyAddedMovies::CDirectoryNodeRecentlyAddedMovies(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_RECENTLY_ADDED_MOVIES, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeRecentlyAddedMovies::GetChildType() const
{
  return NODE_TYPE_TITLE_MOVIES;
}

bool CDirectoryNodeRecentlyAddedMovies::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CStdString strBaseDir=BuildPath();
  bool bSuccess=videodatabase.GetRecentlyAddedMoviesNav(strBaseDir, items);

  videodatabase.Close();

  return bSuccess;
}
