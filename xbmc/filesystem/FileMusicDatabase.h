#pragma once


#include "File.h"

namespace XFILE
{
class CFileMusicDatabase : public IFile
{
public:
  CFileMusicDatabase(void);
  virtual ~CFileMusicDatabase(void);
  virtual bool Open(const CURL& url);
  virtual bool Exists(const CURL& url);
  virtual int Stat(const CURL& url, struct __stat64* buffer);

  virtual unsigned int Read(void* lpBuf, int64_t uiBufSize);
  virtual int64_t Seek(int64_t iFilePosition, int iWhence = SEEK_SET);
  virtual void Close();
  virtual int64_t GetPosition();
  virtual int64_t GetLength();

  static CStdString TranslateUrl(const CURL& url);
protected:
  CFile m_file;
};
}
