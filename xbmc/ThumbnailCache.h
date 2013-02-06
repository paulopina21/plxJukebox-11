#pragma once


#include "utils/StdString.h"

#include <map>

class CCriticalSection;
class CVideoInfoTag;
namespace MUSIC_INFO 
{
  class CMusicInfoTag;
}
class CAlbum;
class CArtist;
class CFileItem;

class CThumbnailCache
{
private:
  CThumbnailCache();
public:
  virtual ~CThumbnailCache();

  static CThumbnailCache* GetThumbnailCache();
  bool ThumbExists(const CStdString& strFileName, bool bAddCache = false);
  void Add(const CStdString& strFileName, bool bExists);
  void Clear();
  bool IsCached(const CStdString& strFileName);

  static CStdString GetMusicThumb(const CStdString &path);
  static CStdString GetAlbumThumb(const CFileItem &item);
  static CStdString GetAlbumThumb(const MUSIC_INFO::CMusicInfoTag *musicInfo);
  static CStdString GetAlbumThumb(const CAlbum &album);
  static CStdString GetAlbumThumb(const CStdString &album, const CStdString &artist);
  static CStdString GetArtistThumb(const CArtist &artist);
  static CStdString GetArtistThumb(const CFileItem &item);
  static CStdString GetArtistThumb(const CStdString &label);
  static CStdString GetActorThumb(const CFileItem &item);
  static CStdString GetActorThumb(const CStdString &label);
  static CStdString GetSeasonThumb(const CFileItem &item);
  static CStdString GetSeasonThumb(const CStdString &label, const CVideoInfoTag *videoInfo = NULL);
  static CStdString GetEpisodeThumb(const CFileItem &item);
  static CStdString GetEpisodeThumb(const CVideoInfoTag *videoInfo);
  static CStdString GetVideoThumb(const CFileItem &item);
  static CStdString GetFanart(const CFileItem &item);
  static CStdString GetThumb(const CStdString &path, const CStdString &path2, bool split = false);
protected:

  static CThumbnailCache* m_pCacheInstance;

  std::map<CStdString, bool> m_Cache;

  static CCriticalSection m_cs;
};
