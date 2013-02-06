#pragma once


#include "MusicInfoTagLoaderMP3.h"

namespace XFILE
{
  class CFile;
}

namespace MUSIC_INFO
{

class CMusicInfoTagLoaderAAC: public CMusicInfoTagLoaderMP3
{
public:
  CMusicInfoTagLoaderAAC(void);
  virtual ~CMusicInfoTagLoaderAAC();
private:
  virtual int ReadDuration(const CStdString& strFileName);
  int ReadID3Length(XFILE::CFile& file);
  int ReadADTSDuration(XFILE::CFile& file, int offset);
  int ReadADIFDuration(XFILE::CFile& file, int offset);
  int ReadMP4Duration(XFILE::CFile& file, int64_t position, int64_t endPosition);
};
}
