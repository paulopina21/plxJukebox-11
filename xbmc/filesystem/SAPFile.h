

// SAPFile.h: interface for the CSAPFile class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "IFile.h"
#include <sstream>

namespace XFILE
{
class CSAPFile : public IFile
{
public:
  CSAPFile();
  virtual ~CSAPFile();
  virtual int64_t GetPosition();
  virtual int64_t GetLength();
  virtual bool Open(const CURL& url);
  virtual bool Exists(const CURL& url);
  virtual int Stat(const CURL& url, struct __stat64* buffer);
  virtual unsigned int Read(void* lpBuf, int64_t uiBufSize);
  virtual int64_t Seek(int64_t iFilePosition, int iWhence = SEEK_SET);
  virtual void Close();

  virtual bool Delete(const CURL& url);
  virtual bool Rename(const CURL& url, const CURL& urlnew);

  virtual int  IoControl(EIoControl request, void* param);
protected:
  std::stringstream m_stream;
  int               m_len;
};

}
