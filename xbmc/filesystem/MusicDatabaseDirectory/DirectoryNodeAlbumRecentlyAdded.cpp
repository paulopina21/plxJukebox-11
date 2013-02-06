

#include "DirectoryNodeAlbumRecentlyAdded.h"
#include "music/MusicDatabase.h"
#include "FileItem.h"

using namespace XFILE::MUSICDATABASEDIRECTORY;

CDirectoryNodeAlbumRecentlyAdded::CDirectoryNodeAlbumRecentlyAdded(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_ALBUM_RECENTLY_ADDED, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeAlbumRecentlyAdded::GetChildType() const
{
  if (GetName()=="-1")
    return NODE_TYPE_ALBUM_RECENTLY_ADDED_SONGS;

  return NODE_TYPE_SONG;
}

CStdString CDirectoryNodeAlbumRecentlyAdded::GetLocalizedName() const
{
  if (GetID() == -1)
    return g_localizeStrings.Get(15102); // All Albums
  CMusicDatabase db;
  if (db.Open())
    return db.GetAlbumById(GetID());
  return "";
}

bool CDirectoryNodeAlbumRecentlyAdded::GetContent(CFileItemList& items) const
{
  CMusicDatabase musicdatabase;
  if (!musicdatabase.Open())
    return false;

  VECALBUMS albums;
  if (!musicdatabase.GetRecentlyAddedAlbums(albums))
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
