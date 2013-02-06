

#include "Bookmark.h"

CBookmark::CBookmark()
{
  Reset();
}

void CBookmark::Reset()
{
  episodeNumber = 0;
  seasonNumber = 0;
  timeInSeconds = 0.0f;
  totalTimeInSeconds = 0.0f;
  type = STANDARD;
}

