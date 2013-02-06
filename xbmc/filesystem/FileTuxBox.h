#pragma once


#include "IFile.h"

namespace XFILE
{
  class CFileTuxBox : public IFile
  {
    public:
      CFileTuxBox();
      virtual ~CFileTuxBox();
      virtual int64_t GetPosition();
      virtual int64_t GetLength();
      virtual bool Open(const CURL& url);
      virtual void Close();
      virtual bool Exists(const CURL& url);
      virtual int Stat(const CURL& url, struct __stat64* buffer);
      virtual unsigned int Read(void* lpBuf, int64_t uiBufSize);
      virtual int64_t Seek(int64_t iFilePosition, int iWhence = SEEK_SET);
    protected:
  };
}



