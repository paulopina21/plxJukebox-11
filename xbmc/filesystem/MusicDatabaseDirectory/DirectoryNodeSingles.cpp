

#include "DirectoryNodeSingles.h"
#include "QueryParams.h"
#include "music/MusicDatabase.h"

using namespace XFILE::MUSICDATABASEDIRECTORY;

CDirectoryNodeSingles::CDirectoryNodeSingles(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_SINGLES, strName, pParent)
{

}

bool CDirectoryNodeSingles::GetContent(CFileItemList& items) const
{
  CMusicDatabase musicdatabase;
  if (!musicdatabase.Open())
    return false;

  CStdString strBaseDir=BuildPath();
  bool bSuccess=musicdatabase.GetSongsByWhere(strBaseDir, "where idAlbum in (select idAlbum from album where strAlbum='')", items);

  musicdatabase.Close();

  return bSuccess;
}
