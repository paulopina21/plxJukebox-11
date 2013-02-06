

/*!
\file TextureManager.h
\brief
*/

#ifndef GUILIB_TEXTUREGL_H
#define GUILIB_TEXTUREGL_H

#include "Texture.h"

#pragma once

#if defined(HAS_GL) || defined(HAS_GLES)

/************************************************************************/
/*    CGLTexture                                                       */
/************************************************************************/
class CGLTexture : public CBaseTexture
{
public:
  CGLTexture(unsigned int width = 0, unsigned int height = 0, unsigned int format = XB_FMT_A8R8G8B8);
  virtual ~CGLTexture();

  void CreateTextureObject();
  virtual void DestroyTextureObject();
  void LoadToGPU();
};

#endif

#endif
