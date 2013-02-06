#include "MusicInfoTagLoaderApe.h"
#include "DllLibapetag.h"
#include "MusicInfoTag.h"
#include "utils/log.h"

using namespace MUSIC_INFO;

CMusicInfoTagLoaderApe::CMusicInfoTagLoaderApe(void)
{}

CMusicInfoTagLoaderApe::~CMusicInfoTagLoaderApe()
{}

bool CMusicInfoTagLoaderApe::Load(const CStdString& strFileName, CMusicInfoTag& tag)
{
  try
  {
    // retrieve the APE Tag info from strFileName
    // and put it in tag
    tag.SetURL(strFileName);
    CAPEv2Tag myTag;
    if (myTag.ReadTag((char*)strFileName.c_str())) // true to check ID3 tag as well
    {
      tag.SetTitle(myTag.GetTitle());
      tag.SetAlbum(myTag.GetAlbum());
      tag.SetArtist(myTag.GetArtist());
      tag.SetAlbumArtist(myTag.GetAlbumArtist());
      tag.SetGenre(myTag.GetGenre());
      tag.SetTrackNumber(myTag.GetTrackNum());
      tag.SetPartOfSet(myTag.GetDiscNum());
      tag.SetComment(myTag.GetComment());
      tag.SetLyrics(myTag.GetLyrics());
      SYSTEMTIME dateTime;
      ZeroMemory(&dateTime, sizeof(SYSTEMTIME));
      dateTime.wYear = atoi(myTag.GetYear());
      tag.SetRating(myTag.GetRating());
      tag.SetReleaseDate(dateTime);
      tag.SetLoaded();
      return true;
    }
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "Tag loader ape: exception in file %s", strFileName.c_str());
  }

  tag.SetLoaded(false);
  return false;
}
