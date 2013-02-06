#pragma once



#include "system.h"

#include <string>
#include <sstream>

class CDVDInputStream;

// buffered class for subtitle reading

class CDVDSubtitleStream
{
public:
  CDVDSubtitleStream();
  virtual ~CDVDSubtitleStream();

  bool Open(const std::string& strFile);
  int Read(char* buf, int buf_size);
  long Seek(long offset, int whence);

  char* ReadLine(char* pBuffer, int iLen);
  //wchar* ReadLineW(wchar* pBuffer, int iLen) { return NULL; };

  std::stringstream m_stringstream;
};

