

#include "MusicInfoTagLoaderDatabase.h"
#include "music/MusicDatabase.h"
#include "filesystem/MusicDatabaseDirectory.h"
#include "filesystem/MusicDatabaseDirectory/DirectoryNode.h"
#include "MusicInfoTag.h"

using namespace MUSIC_INFO;

CMusicInfoTagLoaderDatabase::CMusicInfoTagLoaderDatabase(void)
{
}

CMusicInfoTagLoaderDatabase::~CMusicInfoTagLoaderDatabase()
{
}

bool CMusicInfoTagLoaderDatabase::Load(const CStdString& strFileName, CMusicInfoTag& tag)
{
  tag.SetLoaded(false);
  CMusicDatabase database;
  database.Open();
  XFILE::MUSICDATABASEDIRECTORY::CQueryParams param;
  XFILE::MUSICDATABASEDIRECTORY::CDirectoryNode::GetDatabaseInfo(strFileName,param);

  CSong song;
  if (database.GetSongById(param.GetSongId(),song))
    tag.SetSong(song);

  database.Close();

  return tag.Loaded();
}

