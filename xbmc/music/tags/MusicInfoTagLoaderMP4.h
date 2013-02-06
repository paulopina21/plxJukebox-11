#pragma once


#include "ImusicInfoTagLoader.h"
#include "filesystem/File.h"

namespace MUSIC_INFO
{

class CMusicInfoTagLoaderMP4: public IMusicInfoTagLoader
{
public:
  CMusicInfoTagLoaderMP4(void);
  virtual ~CMusicInfoTagLoaderMP4();

  virtual bool Load(const CStdString& strFileName, CMusicInfoTag& tag);

private:
  unsigned int ReadUnsignedInt( const char* pData );
  void ParseTag( unsigned int metaKey, const char* pMetaData, int metaSize, CMusicInfoTag& tag);
  int GetILSTOffset( const char* pBuffer, int bufferSize );
  int ParseAtom( int64_t startOffset, int64_t stopOffset, CMusicInfoTag& tag );

  unsigned int m_thumbSize;
  BYTE *m_thumbData;
  bool m_isCompilation;

  XFILE::CFile m_file;
};
}
