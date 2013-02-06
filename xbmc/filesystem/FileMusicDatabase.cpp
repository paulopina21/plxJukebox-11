

#include "FileMusicDatabase.h"
#include "music/MusicDatabase.h"
#include "URL.h"
#include "utils/StringUtils.h"
#include "utils/URIUtils.h"

#include <sys/stat.h>

using namespace XFILE;

CFileMusicDatabase::CFileMusicDatabase(void)
{
}

CFileMusicDatabase::~CFileMusicDatabase(void)
{
  Close();
}

CStdString CFileMusicDatabase::TranslateUrl(const CURL& url)
{
  CMusicDatabase musicDatabase;
  if (!musicDatabase.Open())
    return "";

  CStdString strFileName=URIUtils::GetFileName(url.Get());
  CStdString strExtension;
  URIUtils::GetExtension(strFileName, strExtension);
  URIUtils::RemoveExtension(strFileName);

  if (!StringUtils::IsNaturalNumber(strFileName))
    return "";

  long idSong=atol(strFileName.c_str());

  CSong song;
  if (!musicDatabase.GetSongById(idSong, song))
    return "";

  CStdString strExtensionFromDb;
  URIUtils::GetExtension(song.strFileName, strExtensionFromDb);

  if (!strExtensionFromDb.Equals(strExtension))
    return "";

  return song.strFileName;
}

bool CFileMusicDatabase::Open(const CURL& url)
{
  return m_file.Open(TranslateUrl(url));
}

bool CFileMusicDatabase::Exists(const CURL& url)
{
  return !TranslateUrl(url).IsEmpty();
}

int CFileMusicDatabase::Stat(const CURL& url, struct __stat64* buffer)
{
  return m_file.Stat(TranslateUrl(url), buffer);
}

unsigned int CFileMusicDatabase::Read(void* lpBuf, int64_t uiBufSize)
{
  return m_file.Read(lpBuf, uiBufSize);
}

int64_t CFileMusicDatabase::Seek(int64_t iFilePosition, int iWhence /*=SEEK_SET*/)
{
  return m_file.Seek(iFilePosition, iWhence);
}

void CFileMusicDatabase::Close()
{
  m_file.Close();
}

int64_t CFileMusicDatabase::GetPosition()
{
  return m_file.GetPosition();
}

int64_t CFileMusicDatabase::GetLength()
{
  return m_file.GetLength();
}

