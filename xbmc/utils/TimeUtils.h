#pragma once



#include <stdint.h>
#include <time.h>

class CDateTime;
class CTimeSmoother;

int64_t CurrentHostCounter(void);
int64_t CurrentHostFrequency(void);

class CTimeUtils
{
public:
  static void UpdateFrameTime(bool flip); ///< update the frame time.  Not threadsafe
  static unsigned int GetFrameTime(); ///< returns the frame time in MS.  Not threadsafe
  static CDateTime GetLocalTime(time_t time);

private:
  static unsigned int frameTime;
  static CTimeSmoother *frameTimer;
};

