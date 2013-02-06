#pragma once


#include "ThumbLoader.h"
#include "Job.h"

enum ERecentlyAddedFlag
{
  Audio = 0x1,
  Video = 0x2,
  Totals = 0x4
};

class CRecentlyAddedJob : public CJob
{
public:
  CRecentlyAddedJob(int flag);
  bool UpdateVideo();
  bool UpdateMusic();
  bool UpdateTotal();
  virtual bool DoWork();
protected:
  CVideoThumbLoader m_thumbLoader;
private:
  int m_flag;
};
