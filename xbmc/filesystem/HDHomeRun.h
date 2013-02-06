#pragma once


#include "IDirectory.h"
#include "IFile.h"

struct hdhomerun_device;
class DllHdHomeRun;

namespace XFILE
{
  class CDirectoryHomeRun : public IDirectory
  {
    public:
      CDirectoryHomeRun(void);
      virtual ~CDirectoryHomeRun(void);
      virtual bool IsAllowed(const CStdString &strFile) const { return true; };
      virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
    private:
      DllHdHomeRun* m_pdll;
  };
}

namespace XFILE
{
  class CFileHomeRun : public IFile
  {
    public:
      CFileHomeRun();
      ~CFileHomeRun();

      virtual bool          Exists(const CURL& url);
      virtual int64_t       Seek(int64_t iFilePosition, int iWhence);
      virtual int           Stat(const CURL& url, struct __stat64* buffer);
      virtual int64_t       GetPosition();
      virtual int64_t       GetLength();

      virtual bool          Open(const CURL& url);
      virtual void          Close();
      virtual unsigned int  Read(void* lpBuf, int64_t uiBufSize);
      virtual int           GetChunkSize();
    private:
      struct hdhomerun_device_t* m_device;
      DllHdHomeRun* m_pdll;
  };
}
