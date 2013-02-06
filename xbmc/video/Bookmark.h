#pragma once


#include <vector>

#include "utils/StdString.h"

class CBookmark
{
public:
  CBookmark();
  void Reset();
  double timeInSeconds;
  double totalTimeInSeconds;
  CStdString thumbNailImage;
  CStdString playerState;
  CStdString player;
  long seasonNumber;
  long episodeNumber;

  enum EType
  {
    STANDARD = 0,
    RESUME = 1,
    EPISODE = 2
  } type;
};

typedef std::vector<CBookmark> VECBOOKMARKS;

