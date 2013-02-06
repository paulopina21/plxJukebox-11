#pragma once



#include "DVDInputStream.h"

class DllLibbluray;
typedef struct bluray BLURAY;
typedef struct bd_title_info BLURAY_TITLE_INFO;

class CDVDInputStreamBluray 
  : public CDVDInputStream
  , public CDVDInputStream::IDisplayTime
  , public CDVDInputStream::IChapter
  , public CDVDInputStream::ISeekTime
{
public:
  CDVDInputStreamBluray();
  virtual ~CDVDInputStreamBluray();
  virtual bool Open(const char* strFile, const std::string &content);
  virtual void Close();
  virtual int Read(BYTE* buf, int buf_size);
  virtual __int64 Seek(__int64 offset, int whence);
  virtual bool Pause(double dTime) { return false; };
  virtual bool IsEOF();
  virtual __int64 GetLength();
  virtual int GetBlockSize() { return 6144; }

  int GetChapter();
  int GetChapterCount();
  void GetChapterName(std::string& name) {};
  bool SeekChapter(int ch);

  int GetTotalTime();
  int GetTime();
  bool SeekTime(int ms);

  void GetStreamInfo(int pid, char* language);

protected:
  DllLibbluray *m_dll;
  BLURAY* m_bd;
  BLURAY_TITLE_INFO* m_title;
};
