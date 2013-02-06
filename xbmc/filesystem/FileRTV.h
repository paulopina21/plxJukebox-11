

// FileRTV.h: interface for the CFileRTV class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILERTV_H___INCLUDED_)
#define AFX_FILERTV_H___INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IFile.h"

typedef struct rtv_data * RTVD;

namespace XFILE
{

class CFileRTV : public IFile
{
public:
  CFileRTV();
  virtual ~CFileRTV();
  virtual int64_t GetPosition();
  virtual int64_t GetLength();
  virtual bool Open(const CURL& url);
  bool Open(const char* strHostName, const char* strFileName, int iport);
  virtual bool Exists(const CURL& url);
  virtual int Stat(const CURL& url, struct __stat64* buffer);
  virtual unsigned int Read(void* lpBuf, int64_t uiBufSize);
  virtual int64_t Seek(int64_t iFilePosition, int iWhence = SEEK_SET);
  virtual void Close();
protected:
  uint64_t m_fileSize;
  uint64_t m_filePos;
  char m_hostName[255];
  char m_fileName[255];
  int m_iport;
private:
  RTVD m_rtvd;
  bool m_bOpened;

};
}

#endif // !defined(AFX_FILERTV_H___INCLUDED_)
