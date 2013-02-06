

#include "NSFFileDirectory.h"
#include "music/tags/MusicInfoTagLoaderNSF.h"
#include "music/tags/MusicInfoTag.h"

using namespace MUSIC_INFO;
using namespace XFILE;

CNSFFileDirectory::CNSFFileDirectory(void)
{
  m_strExt = "nsfstream";
}

CNSFFileDirectory::~CNSFFileDirectory(void)
{
}

int CNSFFileDirectory::GetTrackCount(const CStdString& strPath)
{
  CMusicInfoTagLoaderNSF nsf;
  nsf.Load(strPath,m_tag);
  m_tag.SetDuration(4*60); // 4 mins

  return nsf.GetStreamCount(strPath);
}
