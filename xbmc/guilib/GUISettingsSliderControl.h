/*!
\file GUISliderControl.h
\brief
*/

#ifndef GUILIB_GUISettingsSliderCONTROL_H
#define GUILIB_GUISettingsSliderCONTROL_H

#pragma once



#include "GUISliderControl.h"
#include "GUIButtonControl.h"

#define SPIN_CONTROL_TYPE_INT    1
#define SPIN_CONTROL_TYPE_FLOAT  2
#define SPIN_CONTROL_TYPE_TEXT   3

/*!
 \ingroup controls
 \brief
 */
class CGUISettingsSliderControl :
      public CGUISliderControl
{
public:
  CGUISettingsSliderControl(int parentID, int controlID, float posX, float posY, float width, float height, float sliderWidth, float sliderHeight, const CTextureInfo &textureFocus, const CTextureInfo &textureNoFocus, const CTextureInfo& backGroundTexture, const CTextureInfo& nibTexture, const CTextureInfo& nibTextureFocus, const CLabelInfo &labelInfo, int iType);
  virtual ~CGUISettingsSliderControl(void);
  virtual CGUISettingsSliderControl *Clone() const { return new CGUISettingsSliderControl(*this); };

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual bool OnAction(const CAction &action);
  virtual void AllocResources();
  virtual void FreeResources(bool immediately = false);
  virtual void DynamicResourceAlloc(bool bOnOff);
  virtual void SetInvalid();
  virtual void SetPosition(float posX, float posY);
  virtual float GetWidth() const { return m_buttonControl.GetWidth();};
  virtual void SetWidth(float width);
  virtual float GetHeight() const { return m_buttonControl.GetHeight();};
  virtual void SetHeight(float height);
  virtual void SetEnabled(bool bEnable);

  void SetText(const std::string &label) {m_buttonControl.SetLabel(label);};
  virtual float GetXPosition() const { return m_buttonControl.GetXPosition();};
  virtual float GetYPosition() const { return m_buttonControl.GetYPosition();};
  virtual CStdString GetDescription() const;
  virtual bool HitTest(const CPoint &point) const { return m_buttonControl.HitTest(point); };

protected:
  virtual bool UpdateColors();
  virtual void ProcessText();

private:
  CGUIButtonControl m_buttonControl;
  CGUILabel m_label;
};
#endif
