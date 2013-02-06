

/*!
\file TextureDX.h
\brief
*/

#ifndef GUILIB_TEXTUREDX_H
#define GUILIB_TEXTUREDX_H

#include "Texture.h"

#pragma once

#ifdef HAS_DX

/************************************************************************/
/*    CDXTexture                                                       */
/************************************************************************/
class CDXTexture : public CBaseTexture
{
public:
  CDXTexture(unsigned int width = 0, unsigned int height = 0, unsigned int format = XB_FMT_UNKNOWN);
  virtual ~CDXTexture();

  void CreateTextureObject();
  void DestroyTextureObject();
  virtual void LoadToGPU();
};

#endif

#endif
