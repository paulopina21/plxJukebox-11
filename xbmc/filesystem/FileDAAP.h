
// FileDAAP.h: interface for the CFileDAAP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEDAAP_H___INCLUDED_)
#define AFX_FILEDAAP_H___INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lib/libXDAAP/client.h"
#include "FileCurl.h"
#include "URL.h"
#include "threads/CriticalSection.h"

class CDaapClient : public CCriticalSection
{
public:

  CDaapClient();
  ~CDaapClient();

  DAAP_SClient *m_pClient;
  DAAP_SClientHost* GetHost(const CStdString &srtHost);
  std::map<CStdString, DAAP_SClientHost*> m_mapHosts;
  typedef std::map<CStdString, DAAP_SClientHost*>::iterator ITHOST;

  DAAP_Status m_Status;

  //Buffers
  int m_iDatabase;
  void *m_pArtistsHead;

  void Release();

protected:
  static void StatusCallback(DAAP_SClient *pClient, DAAP_Status status, int value, void* pContext);
};

extern CDaapClient g_DaapClient;


#include "IFile.h"

namespace XFILE
{
class CFileDAAP : public IFile
{
public:
  CFileDAAP();
  virtual ~CFileDAAP();
  virtual int64_t GetPosition();
  virtual int64_t GetLength();
  virtual bool Open(const CURL& url);
  virtual bool Exists(const CURL& url);
  virtual int Stat(const CURL& url, struct __stat64* buffer);
  virtual unsigned int Read(void* lpBuf, int64_t uiBufSize);
  virtual int64_t Seek(int64_t iFilePosition, int iWhence = SEEK_SET);
  virtual void Close();
  virtual int  IoControl(EIoControl request, void* param);

protected:

  bool StartStreaming();
  bool StopStreaming();

  int64_t m_fileSize; //holds full size
  int64_t m_filePos; //holds current position in file


  DAAP_SClient *m_thisClient;
  DAAP_SClientHost *m_thisHost;
  DAAP_ClientHost_Song m_song;

  bool m_bOpened;

  CStdString m_hashurl; // the url that should be used in hash calculation
  CURL       m_url;     // the complete url we have connected too
  CFileCurl  m_curl;
};
}

#endif // !defined(AFX_FILEDAAP_H___INCLUDED_)


