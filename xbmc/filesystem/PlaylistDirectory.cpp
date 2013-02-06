

#include "PlaylistDirectory.h"
#include "PlayListPlayer.h"
#include "URL.h"
#include "playlists/PlayList.h"

using namespace PLAYLIST;
using namespace XFILE;

CPlaylistDirectory::CPlaylistDirectory()
{

}

CPlaylistDirectory::~CPlaylistDirectory()
{

}

bool CPlaylistDirectory::GetDirectory(const CStdString& strPath, CFileItemList &items)
{
  CURL url(strPath);

  int playlistTyp=PLAYLIST_NONE;
  if (url.GetProtocol()=="playlistmusic")
    playlistTyp=PLAYLIST_MUSIC;
  else if (url.GetProtocol()=="playlistvideo")
    playlistTyp=PLAYLIST_VIDEO;

  if (playlistTyp==PLAYLIST_NONE)
    return false;

  CPlayList& playlist = g_playlistPlayer.GetPlaylist(playlistTyp);
  items.Reserve(playlist.size());

  for (int i = 0; i < playlist.size(); ++i)
  {
    CFileItemPtr item = playlist[i];
    item->SetProperty("playlistposition", i);
    item->SetProperty("playlisttype", playlistTyp);
    //item->m_iprogramCount = i; // the programCount is set as items are added!
    items.Add(item);
  }

  return true;
}
