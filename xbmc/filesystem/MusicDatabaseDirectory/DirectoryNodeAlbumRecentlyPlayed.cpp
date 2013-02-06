

#include "DirectoryNodeAlbumRecentlyPlayed.h"
#include "music/MusicDatabase.h"
#include "FileItem.h"

using namespace XFILE::MUSICDATABASEDIRECTORY;

CDirectoryNodeAlbumRecentlyPlayed::CDirectoryNodeAlbumRecentlyPlayed(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_ALBUM_RECENTLY_PLAYED, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeAlbumRecentlyPlayed::GetChildType() const
{
  if (GetName()=="-1")
    return NODE_TYPE_ALBUM_RECENTLY_PLAYED_SONGS;

  return NODE_TYPE_SONG;
}

CStdString CDirectoryNodeAlbumRecentlyPlayed::GetLocalizedName() const
{
  if (GetID() == -1)
    return g_localizeStrings.Get(15102); // All Albums
  CMusicDatabase db;
  if (db.Open())
    return db.GetAlbumById(GetID());
  return "";
}

bool CDirectoryNodeAlbumRecentlyPlayed::GetContent(CFileItemList& items) const
{
  CMusicDatabase musicdatabase;
  if (!musicdatabase.Open())
    return false;

  VECALBUMS albums;
  if (!musicdatabase.GetRecentlyPlayedAlbums(albums))
  {
    musicdatabase.Close();
    return false;
  }

  for (int i=0; i<(int)albums.size(); ++i)
  {
    CAlbum& album=albums[i];
    CStdString strDir;
    strDir.Format("%s%ld/", BuildPath().c_str(), album.idAlbum);
    CFileItemPtr pItem(new CFileItem(strDir, album));
    items.Add(pItem);
  }


  musicdatabase.Close();

  return true;
}
