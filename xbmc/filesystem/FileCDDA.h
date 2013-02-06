#pragma once


#include "system.h" // for HAS_DVD_DRIVE

#ifdef HAS_DVD_DRIVE

#include "IFile.h"
#include "storage/cdioSupport.h"

namespace XFILE
{
class CFileCDDA : public IFile
{
public:
  CFileCDDA(void);
  virtual ~CFileCDDA(void);
  virtual bool Open(const CURL& url);
  virtual bool Exists(const CURL& url);
  virtual int Stat(const CURL& url, struct __stat64* buffer);

  virtual unsigned int Read(void* lpBuf, int64_t uiBufSize);
  virtual int64_t Seek(int64_t iFilePosition, int iWhence = SEEK_SET);
  virtual void Close();
  virtual int64_t GetPosition();
  virtual int64_t GetLength();
  virtual int GetChunkSize();

protected:
  bool IsValidFile(const CURL& url);
  int GetTrackNum(const CURL& url);

protected:
  CdIo_t* m_pCdIo;
  lsn_t m_lsnStart;  // Start of m_iTrack in logical sector number
  lsn_t m_lsnCurrent; // Position inside the track in logical sector number
  lsn_t m_lsnEnd;   // End of m_iTrack in logical sector number
  MEDIA_DETECT::CLibcdio* m_cdio;
};
}

#endif

