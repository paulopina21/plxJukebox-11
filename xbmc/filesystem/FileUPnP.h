#pragma once


#include "IFile.h"

namespace XFILE
{
  class CFileUPnP : public IFile
  {
    public:
      CFileUPnP();
      virtual ~CFileUPnP();
      virtual bool Open(const CURL& url);      
      virtual bool Exists(const CURL& url);
      virtual int Stat(const CURL& url, struct __stat64* buffer);
      
      virtual unsigned int Read(void* lpBuf, int64_t uiBufSize) {return -1;}
      virtual int64_t Seek(int64_t iFilePosition, int iWhence = SEEK_SET) {return -1;}
      virtual void Close(){}
      virtual int64_t GetPosition() {return -1;}
      virtual int64_t GetLength() {return -1;}
  };
}
