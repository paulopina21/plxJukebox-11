

//------------------------------
// CApeTag in 2005 by JMarshall
//------------------------------
#include "cores/paplayer/ReplayGain.h"
#include "DllLibapetag.h"

namespace MUSIC_INFO
{

#pragma once

class CAPEv2Tag
{
public:
  CAPEv2Tag(void);
  virtual ~CAPEv2Tag(void);
  bool ReadTag(const char* filename);
  CStdString GetTitle() { return m_strTitle; }
  CStdString GetArtist() { return m_strArtist; }
  CStdString GetYear() { return m_strYear; }
  CStdString GetAlbum() { return m_strAlbum; }
  CStdString GetAlbumArtist() { return m_strAlbumArtist; };
  CStdString GetGenre() { return m_strGenre; }
  int GetTrackNum() { return m_nTrackNum; }
  int GetDiscNum() { return m_nDiscNum; }
  CStdString GetMusicBrainzTrackID() { return m_strMusicBrainzTrackID; }
  CStdString GetMusicBrainzArtistID() { return m_strMusicBrainzArtistID; }
  CStdString GetMusicBrainzAlbumID() { return m_strMusicBrainzAlbumID; }
  CStdString GetMusicBrainzAlbumArtistID() { return m_strMusicBrainzAlbumArtistID; }
  CStdString GetMusicBrainzTRMID() { return m_strMusicBrainzTRMID; }
  CStdString GetComment() { return m_strComment; };
  CStdString GetLyrics() { return m_strLyrics; };
  char GetRating() { return m_rating; };
  void GetReplayGainFromTag(apetag *tag);
  const CReplayGain &GetReplayGain() { return m_replayGain; };

  static size_t fread_callback(void *ptr, size_t size, size_t nmemb, void *fp);  
  static int fseek_callback(void *fp, long int offset, int whence);
  static long ftell_callback(void *fp);

protected:
  CStdString m_strTitle;
  CStdString m_strArtist;
  CStdString m_strYear;
  CStdString m_strAlbum;
  CStdString m_strAlbumArtist;
  CStdString m_strGenre;
  int m_nTrackNum;
  int m_nDiscNum;
  CStdString m_strMusicBrainzTrackID;
  CStdString m_strMusicBrainzArtistID;
  CStdString m_strMusicBrainzAlbumID;
  CStdString m_strMusicBrainzAlbumArtistID;
  CStdString m_strMusicBrainzTRMID;
  CStdString m_strComment;
  CStdString m_strLyrics;
  CReplayGain m_replayGain;
  int64_t m_nDuration;
  char m_rating;

  DllLibApeTag m_dll;
};
}
