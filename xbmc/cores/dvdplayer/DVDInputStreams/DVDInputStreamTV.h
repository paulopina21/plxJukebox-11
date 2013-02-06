#pragma once



#include "DVDInputStream.h"

namespace XFILE {
class IFile;
class ILiveTVInterface;
class IRecordable;
}

class CDVDInputStreamTV
  : public CDVDInputStream
  , public CDVDInputStream::IChannel
{
public:
  CDVDInputStreamTV();
  virtual ~CDVDInputStreamTV();
  virtual bool    Open(const char* strFile, const std::string &content);
  virtual void    Close();
  virtual int     Read(BYTE* buf, int buf_size);
  virtual __int64 Seek(__int64 offset, int whence);
  virtual bool Pause(double dTime) { return false; };
  virtual bool    IsEOF();
  virtual __int64 GetLength();

  virtual bool    NextStream();
  virtual int     GetBlockSize();


  bool            NextChannel();
  bool            PrevChannel();
  bool            SelectChannel(unsigned int channel);

  int             GetTotalTime();
  int             GetStartTime();

  bool            SeekTime(int iTimeInMsec);

  bool            CanRecord();
  bool            IsRecording();
  bool            Record(bool bOnOff);

  bool            UpdateItem(CFileItem& item);

protected:
  XFILE::IFile*            m_pFile;
  XFILE::ILiveTVInterface* m_pLiveTV;
  XFILE::IRecordable*      m_pRecordable;
  bool m_eof;
};

