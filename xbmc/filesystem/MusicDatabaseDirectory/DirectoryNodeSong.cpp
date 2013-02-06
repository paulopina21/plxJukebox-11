

#include "DirectoryNodeSong.h"
#include "QueryParams.h"
#include "music/MusicDatabase.h"

using namespace XFILE::MUSICDATABASEDIRECTORY;

CDirectoryNodeSong::CDirectoryNodeSong(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_SONG, strName, pParent)
{

}

bool CDirectoryNodeSong::GetContent(CFileItemList& items) const
{
  CMusicDatabase musicdatabase;
  if (!musicdatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  CStdString strBaseDir=BuildPath();
  bool bSuccess=musicdatabase.GetSongsNav(strBaseDir, items, params.GetGenreId(), params.GetArtistId(), params.GetAlbumId());

  musicdatabase.Close();

  return bSuccess;
}
