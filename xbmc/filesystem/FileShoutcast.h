

// FileShoutcast.h: interface for the CFileShoutcast class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "IFile.h"
#include "FileCurl.h"
#include "utils/StdString.h"
#include "music/tags/MusicInfoTag.h"

namespace XFILE
{
class CFileShoutcast : public IFile
{
public:
  CFileShoutcast();
  virtual ~CFileShoutcast();
  virtual int64_t GetPosition();
  virtual int64_t GetLength();
  virtual bool Open(const CURL& url);
  virtual bool Exists(const CURL& url) { return true;};
  virtual int Stat(const CURL& url, struct __stat64* buffer) { errno = ENOENT; return -1; };
  virtual unsigned int Read(void* lpBuf, int64_t uiBufSize);
  virtual int64_t Seek(int64_t iFilePosition, int iWhence = SEEK_SET);
  virtual void Close();
protected:
  void ExtractTagInfo(const char* buf);
  void ReadTruncated(char* buf2, int size);

  unsigned int m_lastTime;
  CFileCurl m_file;
  int m_metaint;
  int m_discarded; // data used for tags
  int m_currint;
  char* m_buffer; // buffer used for tags
  MUSIC_INFO::CMusicInfoTag m_tag;
};
}

