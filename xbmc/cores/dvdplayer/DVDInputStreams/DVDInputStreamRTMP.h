#pragma once


#ifdef HAS_LIBRTMP

#include "DVDInputStream.h"
#include "DllLibRTMP.h"

class CDVDInputStreamRTMP 
  : public CDVDInputStream
  , public CDVDInputStream::ISeekTime
{
public:
  CDVDInputStreamRTMP();
  virtual ~CDVDInputStreamRTMP();
  virtual bool    Open(const char* strFile, const std::string &content);
  virtual void    Close();
  virtual int     Read(BYTE* buf, int buf_size);
  virtual __int64 Seek(__int64 offset, int whence);
  bool            SeekTime(int iTimeInMsec);
  virtual bool Pause(double dTime);
  virtual bool    IsEOF();
  virtual __int64 GetLength();

  virtual bool    NextStream();

  CCriticalSection m_RTMPSection;

protected:
  bool       m_eof;
  bool       m_bPaused;
  char*      m_sStreamPlaying;
  std::vector<CStdString> m_optionvalues;

  RTMP       *m_rtmp;
  DllLibRTMP m_libRTMP;
};

#endif
