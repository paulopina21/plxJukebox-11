/*!
\file GUITextureD3D.h
\brief
*/

#ifndef GUILIB_GUITEXTURED3D_H
#define GUILIB_GUITEXTURED3D_H

#pragma once



#include "GUITexture.h"

#ifdef HAS_DX

class CGUITextureD3D : public CGUITextureBase
{
public:
  CGUITextureD3D(float posX, float posY, float width, float height, const CTextureInfo& texture);
  static void DrawQuad(const CRect &coords, color_t color, CBaseTexture *texture = NULL, const CRect *texCoords = NULL);
protected:
  void Begin(color_t color);
  void Draw(float *x, float *y, float *z, const CRect &texture, const CRect &diffuse, int orientation);
  void End();
private:
  color_t m_col;
};

#endif

#endif