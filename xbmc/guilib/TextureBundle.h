#pragma once



#include "utils/StdString.h"
#include "TextureBundleXPR.h"
#include "TextureBundleXBT.h"

class CTextureBundle
{
public:
  CTextureBundle(void);
  ~CTextureBundle(void);

  void Cleanup();

  void SetThemeBundle(bool themeBundle);
  bool HasFile(const CStdString& Filename);
  void GetTexturesFromPath(const CStdString &path, std::vector<CStdString> &textures);
  static CStdString Normalize(const CStdString &name);

  bool LoadTexture(const CStdString& Filename, CBaseTexture** ppTexture, int &width, int &height);

  int LoadAnim(const CStdString& Filename, CBaseTexture*** ppTextures, int &width, int &height, int& nLoops, int** ppDelays);

private:
  CTextureBundleXPR m_tbXPR;
  CTextureBundleXBT m_tbXBT;

  bool m_useXPR;
  bool m_useXBT;
};


