

/*!
\file GUIFont.h
\brief
*/

#ifndef CGUILIB_GUIFONTTTF_DX_H
#define CGUILIB_GUIFONTTTF_DX_H
#pragma once


#include "GUIFontTTF.h"
#include "D3DResource.h"

/*!
 \ingroup textures
 \brief
 */
class CGUIFontTTFDX : public CGUIFontTTFBase
{
public:
  CGUIFontTTFDX(const CStdString& strFileName);
  virtual ~CGUIFontTTFDX(void);

  virtual void Begin();
  virtual void End();

protected:
  virtual CBaseTexture* ReallocTexture(unsigned int& newHeight);
  virtual bool CopyCharToTexture(FT_BitmapGlyph bitGlyph, Character *ch);
  virtual void DeleteHardwareTexture();
  CD3DTexture *m_speedupTexture;  // extra texture to speed up reallocations when the main texture is in d3dpool_default.
                                  // that's the typical situation of Windows Vista and above.
  uint16_t* m_index;
  unsigned  m_index_size;
};

#endif
