/*!
\file GUITextureGLES.h
\brief
*/

#ifndef GUILIB_GUITEXTUREGLES_H
#define GUILIB_GUITEXTUREGLES_H

#pragma once



#include "GUITexture.h"

class CGUITextureGLES : public CGUITextureBase
{
public:
  CGUITextureGLES(float posX, float posY, float width, float height, const CTextureInfo& texture);
  static void DrawQuad(const CRect &coords, color_t color, CBaseTexture *texture = NULL, const CRect *texCoords = NULL);
protected:
  void Begin(color_t color);
  void Draw(float *x, float *y, float *z, const CRect &texture, const CRect &diffuse, int orientation);
  void End();

  GLubyte m_col [4][4];
  GLfloat m_vert[4][3];
  GLfloat m_tex0[4][2];
  GLfloat m_tex1[4][2];
};

#endif
