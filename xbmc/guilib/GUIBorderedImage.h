#ifndef CGUIBorderedImage_H
#define CGUIBorderedImage_H



#include "GUIControl.h"
#include "TextureManager.h"
#include "GUIImage.h"

class CGUIBorderedImage : public CGUIImage
{
public:
  CGUIBorderedImage(int parentID, int controlID, float posX, float posY, float width, float height, const CTextureInfo& texture, const CTextureInfo& borderTexture, const CRect &borderSize);
  CGUIBorderedImage(const CGUIBorderedImage &right);
  virtual ~CGUIBorderedImage(void);
  virtual CGUIBorderedImage *Clone() const { return new CGUIBorderedImage(*this); };

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual void AllocResources();
  virtual void FreeResources(bool immediately = false);
  virtual void DynamicResourceAlloc(bool bOnOff);
  
  virtual CRect CalcRenderRegion() const;

protected:
  CGUITexture m_borderImage;
  CRect m_borderSize;
};

#endif
