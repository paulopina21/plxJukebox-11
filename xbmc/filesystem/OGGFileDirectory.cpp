

#include "OGGFileDirectory.h"
#include "music/tags/OggTag.h"

using namespace MUSIC_INFO;
using namespace XFILE;

COGGFileDirectory::COGGFileDirectory(void)
{
  m_strExt = "oggstream";
}

COGGFileDirectory::~COGGFileDirectory(void)
{
}

int COGGFileDirectory::GetTrackCount(const CStdString& strPath)
{
  COggTag tag;
  return tag.GetStreamCount(strPath);
}
