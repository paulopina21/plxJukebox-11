#pragma once


#include "File.h"

namespace XFILE
{
class CFileFileReader : public IFile
{
public:
  CFileFileReader();
  virtual ~CFileFileReader();
  virtual int64_t GetPosition();
  virtual int64_t GetLength();
  virtual bool Open(const CURL& url);
  virtual bool Exists(const CURL& url);
  virtual int Stat(const CURL& url, struct __stat64* buffer);
  virtual unsigned int Read(void* lpBuf, int64_t uiBufSize);
  virtual int Write(const void* lpBuf, int64_t uiBufSize);
  virtual int64_t Seek(int64_t iFilePosition, int iWhence = SEEK_SET);
  virtual void Close();

  virtual bool OpenForWrite(const CURL& url, bool bOverWrite = false);
  protected:
  CFile m_reader;
};

}


