/*!
\file GUIFontManager.h
\brief
*/

#ifndef GUILIB_FONTMANAGER_H
#define GUILIB_FONTMANAGER_H

#pragma once



#include "GraphicContext.h"
#include "IMsgTargetCallback.h"

// Forward
class CGUIFont;
class CGUIFontTTFBase;
class TiXmlDocument;
class TiXmlNode;

struct OrigFontInfo
{
   int size;
   float aspect;
   CStdString fontFilePath;
   CStdString fileName;
   RESOLUTION_INFO sourceRes;
   bool preserveAspect;
   bool border;
};

/*!
 \ingroup textures
 \brief
 */
class GUIFontManager : public IMsgTargetCallback
{
public:
  GUIFontManager(void);
  virtual ~GUIFontManager(void);

  virtual bool OnMessage(CGUIMessage &message);

  void Unload(const CStdString& strFontName);
  void LoadFonts(const CStdString& strFontSet);
  CGUIFont* LoadTTF(const CStdString& strFontName, const CStdString& strFilename, color_t textColor, color_t shadowColor, const int iSize, const int iStyle, bool border = false, float lineSpacing = 1.0f, float aspect = 1.0f, const RESOLUTION_INFO *res = NULL, bool preserveAspect = false);
  CGUIFont* GetFont(const CStdString& strFontName, bool fallback = true);

  /*! \brief return a default font
   \param border whether the font should be a font with an outline
   \return the font.  NULL if no default font can be found.
   */
  CGUIFont* GetDefaultFont(bool border = false);

  void Clear();
  void FreeFontFile(CGUIFontTTFBase *pFont);

  bool IsFontSetUnicode() { return m_fontsetUnicode; }
  bool IsFontSetUnicode(const CStdString& strFontSet);
  bool GetFirstFontSetUnicode(CStdString& strFontSet);

protected:
  void RescaleFontSizeAndAspect(float *size, float *aspect, const RESOLUTION_INFO &sourceRes, bool preserveAspect) const;
  void ReloadTTFFonts();
  void LoadFonts(const TiXmlNode* fontNode);
  CGUIFontTTFBase* GetFontFile(const CStdString& strFontFile);
  bool OpenFontFile(TiXmlDocument& xmlDoc);

  std::vector<CGUIFont*> m_vecFonts;
  std::vector<CGUIFontTTFBase*> m_vecFontFiles;
  std::vector<OrigFontInfo> m_vecFontInfo;
  bool m_fontsetUnicode;
  RESOLUTION_INFO m_skinResolution;
  bool m_canReload;
};

/*!
 \ingroup textures
 \brief
 */
extern GUIFontManager g_fontManager;
#endif
