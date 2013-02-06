

#include "ASAPFileDirectory.h"
#include "File.h"
#include "music/tags/MusicInfoTagLoaderASAP.h"

using namespace XFILE;

CASAPFileDirectory::CASAPFileDirectory()
{
  m_strExt = "asapstream";
}

CASAPFileDirectory::~CASAPFileDirectory()
{
}

int CASAPFileDirectory::GetTrackCount(const CStdString &strPath)
{
  if (!m_dll.Load())
    return 0;

  MUSIC_INFO::CMusicInfoTagLoaderASAP loader;
  loader.Load(strPath,m_tag);
  m_tag.SetDuration(0); // ignore duration or all songs get duration of track 1

  return m_dll.asapGetSongs(strPath.c_str());
}
