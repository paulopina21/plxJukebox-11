

#include "DirectoryNodeSongTop100.h"
#include "music/MusicDatabase.h"

using namespace XFILE::MUSICDATABASEDIRECTORY;

CDirectoryNodeSongTop100::CDirectoryNodeSongTop100(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_SONG_TOP100, strName, pParent)
{

}

bool CDirectoryNodeSongTop100::GetContent(CFileItemList& items) const
{
  CMusicDatabase musicdatabase;
  if (!musicdatabase.Open())
    return false;

  CStdString strBaseDir=BuildPath();
  bool bSuccess=musicdatabase.GetTop100(strBaseDir, items);

  musicdatabase.Close();

  return bSuccess;
}
