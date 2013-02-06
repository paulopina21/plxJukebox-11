#pragma once



#include "utils/StdString.h"
#include <map>
#include "XBTFReader.h"

class CBaseTexture;

class CTextureBundleXBT
{
public:
  CTextureBundleXBT(void);
  ~CTextureBundleXBT(void);

  void Cleanup();
  void SetThemeBundle(bool themeBundle);
  bool HasFile(const CStdString& Filename);
  void GetTexturesFromPath(const CStdString &path, std::vector<CStdString> &textures);
  static CStdString Normalize(const CStdString &name);

  bool LoadTexture(const CStdString& Filename, CBaseTexture** ppTexture,
                       int &width, int &height);

  int LoadAnim(const CStdString& Filename, CBaseTexture*** ppTextures,
                int &width, int &height, int& nLoops, int** ppDelays);

private:
  bool OpenBundle();
  bool ConvertFrameToTexture(const CStdString& name, CXBTFFrame& frame, CBaseTexture** ppTexture);

  time_t m_TimeStamp;

  bool m_themeBundle;
  CXBTFReader m_XBTFReader;
};


