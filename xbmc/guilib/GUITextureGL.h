/*!
\file GUITextureGL.h
\brief
*/

#ifndef GUILIB_GUITEXTUREGL_H
#define GUILIB_GUITEXTUREGL_H

#pragma once



#include "GUITexture.h"

class CGUITextureGL : public CGUITextureBase
{
public:
  CGUITextureGL(float posX, float posY, float width, float height, const CTextureInfo& texture);
  static void DrawQuad(const CRect &coords, color_t color, CBaseTexture *texture = NULL, const CRect *texCoords = NULL);
protected:
  void Begin(color_t color);
  void Draw(float *x, float *y, float *z, const CRect &texture, const CRect &diffuse, int orientation);
  void End();
private:
  GLubyte m_col[4];
};

#endif
