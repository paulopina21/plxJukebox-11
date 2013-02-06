

#include "MusicInfoTagLoaderShn.h"
#include "MusicInfoTag.h"
#include "utils/log.h"

using namespace MUSIC_INFO;

CMusicInfoTagLoaderSHN::CMusicInfoTagLoaderSHN(void)
{}

CMusicInfoTagLoaderSHN::~CMusicInfoTagLoaderSHN()
{}

bool CMusicInfoTagLoaderSHN::Load(const CStdString& strFileName, CMusicInfoTag& tag)
{
  try
  {

    tag.SetURL(strFileName);
    tag.SetDuration((long)0); //TODO: Use libavformat to calculate duration.
    tag.SetLoaded(false);

    return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "Tag loader shn: exception in file %s", strFileName.c_str());
  }

  tag.SetLoaded(false);
  return false;
}
