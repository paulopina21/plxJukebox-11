#pragma once



#include "utils/StdString.h"
#include <stdint.h>
#include <map>

class CAutoTexBuffer;
class CBaseTexture;

class CTextureBundleXPR
{
  struct FileHeader_t
  {
    uint32_t Offset;
    uint32_t UnpackedSize;
    uint32_t PackedSize;
  };

  FILE*  m_hFile;
  time_t m_TimeStamp;

  std::map<CStdString, FileHeader_t> m_FileHeaders;
  typedef std::map<CStdString, FileHeader_t>::iterator iFiles;

  bool m_themeBundle;

  bool OpenBundle();
  bool LoadFile(const CStdString& Filename, CAutoTexBuffer& UnpackedBuf);

public:
  CTextureBundleXPR(void);
  ~CTextureBundleXPR(void);

  void Cleanup();

  void SetThemeBundle(bool themeBundle);
  bool HasFile(const CStdString& Filename);
  void GetTexturesFromPath(const CStdString &path, std::vector<CStdString> &textures);
  static CStdString Normalize(const CStdString &name);

  bool LoadTexture(const CStdString& Filename, CBaseTexture** ppTexture,
                       int &width, int &height);

  int LoadAnim(const CStdString& Filename, CBaseTexture*** ppTextures,
                int &width, int &height, int& nLoops, int** ppDelays);
};


