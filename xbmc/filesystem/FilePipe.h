

// FilePipe.h: interface for the CFilePipe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEPIPE_H__DD2B0A9E_4971_4A29_B525_78CEFCDAF4A1__INCLUDED_)
#define AFX_FILEPIPE_H__DD2B0A9E_4971_4A29_B525_78CEFCDAF4A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IFile.h"
#include "utils/AutoPtrHandle.h"
#include "utils/StdString.h"
#include "threads/Event.h"
#include "threads/CriticalSection.h"
#include "utils/RingBuffer.h"
#include "PipesManager.h"

namespace XFILE
{
  
class CFilePipe : public IFile, public IPipeListener
{
public:
  CFilePipe();
  virtual ~CFilePipe();
  virtual int64_t GetPosition();
  virtual int64_t GetLength();
  virtual void SetLength(int64_t len);
  virtual bool Open(const CURL& url);
  virtual bool Exists(const CURL& url);
  virtual int Stat(const CURL& url, struct __stat64* buffer);
  virtual int Stat(struct __stat64* buffer);
  virtual unsigned int Read(void* lpBuf, int64_t uiBufSize);
  virtual int Write(const void* lpBuf, int64_t uiBufSize);
  virtual int64_t Seek(int64_t iFilePosition, int iWhence = SEEK_SET);
  virtual void Close();
  virtual void Flush();
  virtual __int64	GetAvailableRead();

  virtual bool OpenForWrite(const CURL& url, bool bOverWrite = false);

  virtual bool Delete(const CURL& url);
  virtual bool Rename(const CURL& url, const CURL& urlnew);
  virtual int IoControl(int request, void* param);
  
  CStdString GetName() const;
  
  virtual void OnPipeOverFlow();
  virtual void OnPipeUnderFlow();

  void AddListener(IPipeListener *l);
  void RemoveListener(IPipeListener *l);

  void SetEof();
  bool IsEof();
  bool IsEmpty();
  bool IsClosed();
  
  void SetOpenThreashold(int threashold);

protected:
  int64_t m_pos;
  int64_t m_length;
  
  XFILE::Pipe *m_pipe;
  
  CCriticalSection m_lock;
  std::vector<XFILE::IPipeListener *> m_listeners;
};

}
#endif // !defined(AFX_FILEPIPE_H__DD2B0A9E_4971_4A29_B525_78CEFCDAF4A1__INCLUDED_)
