

/*!
\file GUIFont.h
\brief
*/

#ifndef CGUILIB_GUIFONTTTF_GL_H
#define CGUILIB_GUIFONTTTF_GL_H
#pragma once


#include "GUIFontTTF.h"


/*!
 \ingroup textures
 \brief
 */
class CGUIFontTTFGL : public CGUIFontTTFBase
{
public:
  CGUIFontTTFGL(const CStdString& strFileName);
  virtual ~CGUIFontTTFGL(void);

  virtual void Begin();
  virtual void End();

protected:
  virtual CBaseTexture* ReallocTexture(unsigned int& newHeight);
  virtual bool CopyCharToTexture(FT_BitmapGlyph bitGlyph, Character *ch);
  virtual void DeleteHardwareTexture();

};

#endif
