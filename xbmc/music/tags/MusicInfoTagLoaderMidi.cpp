

#include "MusicInfoTagLoaderMidi.h"
#include "utils/URIUtils.h"
#include "MusicInfoTag.h"

using namespace XFILE;
using namespace MUSIC_INFO;


CMusicInfoTagLoaderMidi::CMusicInfoTagLoaderMidi()
  : IMusicInfoTagLoader()
{
}


CMusicInfoTagLoaderMidi::~CMusicInfoTagLoaderMidi()
{
}

// There is no reliable tag information in MIDI files. There is a 'title' field (@T), but it looks
// like everyone puts there song title, artist name, the name of the person who created the lyrics and
// greetings to their friends and family. Therefore we return the song title as file name, and the
// song artist as parent directory.
// A good intention of creating a pattern-based artist/song recognition engine failed greatly. Simple formats
// like %A-%T fail greatly with artists like A-HA and songs like "Ob-la-Di ob-la-Da.mid". So if anyone has
// a good idea which would include cases from above, I'd be happy to hear about it.
bool CMusicInfoTagLoaderMidi::Load(const CStdString & strFileName, CMusicInfoTag & tag)
{
  tag.SetURL(strFileName);

  CStdString path, title;
  URIUtils::Split( strFileName, path, title);
  URIUtils::RemoveExtension( title );

  tag.SetTitle( title );

  URIUtils::RemoveSlashAtEnd(path );

  if ( !path.IsEmpty() )
  {
    CStdString artist = URIUtils::GetFileName( path );
    if ( !artist.IsEmpty() )
      tag.SetArtist( artist );
  }

  tag.SetLoaded(true);
  return true;
}
