#pragma once


#include "IFile.h"
#include "CacheStrategy.h"
#include "threads/CriticalSection.h"
#include "File.h"
#include "threads/Thread.h"

namespace XFILE
{

  class CFileCache : public IFile, public CThread
  {
  public:
    CFileCache();
    CFileCache(CCacheStrategy *pCache, bool bDeleteCache=true);
    virtual ~CFileCache();

    void SetCacheStrategy(CCacheStrategy *pCache, bool bDeleteCache=true);

    // CThread methods
    virtual void Process();
    virtual void OnExit();
    virtual void StopThread(bool bWait = true);

    // IFIle methods
    virtual bool          Open(const CURL& url);
    virtual void          Close();
    virtual bool          Exists(const CURL& url);
    virtual int           Stat(const CURL& url, struct __stat64* buffer);

    virtual unsigned int  Read(void* lpBuf, int64_t uiBufSize);

    virtual int64_t       Seek(int64_t iFilePosition, int iWhence);
    virtual int64_t       GetPosition();
    virtual int64_t       GetLength();

    virtual int           IoControl(EIoControl request, void* param);

    IFile *GetFileImp();

    virtual CStdString GetContent();

  private:
    CCacheStrategy *m_pCache;
    bool      m_bDeleteCache;
    int        m_seekPossible;
    CFile      m_source;
    CStdString    m_sourcePath;
    CEvent      m_seekEvent;
    CEvent      m_seekEnded;
    int64_t      m_nSeekResult;
    int64_t      m_seekPos;
    int64_t      m_readPos;
    int64_t      m_writePos;
    unsigned     m_writeRate;
    unsigned     m_writeRateActual;
    bool         m_cacheFull;
    CCriticalSection m_sync;
  };

}
