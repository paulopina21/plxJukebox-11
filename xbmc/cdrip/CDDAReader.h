#ifndef _CCDDAREADER_H
#define _CCDDAREADER_H



#define CDDARIP_OK    0
#define CDDARIP_ERR   1
#define CDDARIP_DONE  2

#include "threads/Thread.h"

#include "FileItem.h"
#include "filesystem/File.h"
#include "threads/Event.h"

struct RipBuffer
{
  int iRipError;
  long lBytesRead;
  BYTE* pbtStream;
  HANDLE hEvent;
};

class CCDDAReader : public CThread
{
public:
  CCDDAReader();
  virtual ~CCDDAReader();
  int GetData(BYTE** stream, long& lBytes);
  bool Init(const char* strFileName);
  bool DeInit();
  int GetPercent();
  int GetTrackLength();
protected:
  void Process();
  int ReadChunk();

  long m_lBufferSize;

  RipBuffer m_sRipBuffer[2]; // hold space for 2 buffers
  int m_iCurrentBuffer;   // 0 or 1

  CEvent m_hReadEvent;       // data is fetched
  CEvent m_hDataReadyEvent;  // data is ready to be fetched

  bool m_iInitialized;

  XFILE::CFile m_fileCdda;
};

#endif // _CCDDAREADER_H
