

// WINFileSMB.h: interface for the CWINFileSMB class.
//
//////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "filesystem/IFile.h"
#include "utils/AutoPtrHandle.h"

namespace XFILE
{
class CWINFileSMB : public IFile
{
public:
  CWINFileSMB();
  virtual ~CWINFileSMB();
  virtual int64_t GetPosition();
  virtual int64_t GetLength();
  virtual bool Open(const CURL& url);
  virtual bool Exists(const CURL& url);
  virtual int Stat(const CURL& url, struct __stat64* buffer);
  virtual int Stat(struct __stat64* buffer);
  virtual unsigned int Read(void* lpBuf, int64_t uiBufSize);
  virtual int Write(const void* lpBuf, int64_t uiBufSize);
  virtual int64_t Seek(int64_t iFilePosition, int iWhence = SEEK_SET);
  virtual void Close();
  virtual void Flush();

  virtual bool OpenForWrite(const CURL& url, bool bOverWrite = false);

  virtual bool Delete(const CURL& url);
  virtual bool Rename(const CURL& url, const CURL& urlnew);
  virtual bool SetHidden(const CURL& url, bool hidden);

  virtual int IoControl(EIoControl request, void* param);
protected:
  CStdString GetLocal(const CURL &url); /* crate a properly format path from an url */
  AUTOPTR::CAutoPtrHandle m_hFile;
  int64_t m_i64FilePos;
};

}
