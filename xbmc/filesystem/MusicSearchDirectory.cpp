

#include "threads/SystemClock.h"
#include "MusicSearchDirectory.h"
#include "music/MusicDatabase.h"
#include "URL.h"
#include "FileItem.h"
#include "utils/log.h"
#include "utils/TimeUtils.h"
#include "guilib/LocalizeStrings.h"

using namespace XFILE;

CMusicSearchDirectory::CMusicSearchDirectory(void)
{
}

CMusicSearchDirectory::~CMusicSearchDirectory(void)
{
}

bool CMusicSearchDirectory::GetDirectory(const CStdString& strPath, CFileItemList &items)
{
  // break up our path
  // format is:  musicsearch://<url encoded search string>
  CURL url(strPath);
  CStdString search(url.GetHostName());

  if (search.IsEmpty())
    return false;

  // and retrieve the search details
  items.SetPath(strPath);
  unsigned int time = XbmcThreads::SystemClockMillis();
  CMusicDatabase db;
  db.Open();
  db.Search(search, items);
  db.Close();
  CLog::Log(LOGDEBUG, "%s (%s) took %u ms",
            __FUNCTION__, strPath.c_str(), XbmcThreads::SystemClockMillis() - time);
  items.SetLabel(g_localizeStrings.Get(137)); // Search
  return true;
}

bool CMusicSearchDirectory::Exists(const char* strPath)
{
  return true;
}
