/*!
\file GUIToggleButtonControl.h
\brief
*/

#ifndef GUILIB_GUITOGGLEBUTTONCONTROL_H
#define GUILIB_GUITOGGLEBUTTONCONTROL_H

#pragma once



#include "GUIButtonControl.h"

/*!
 \ingroup controls
 \brief
 */
class CGUIToggleButtonControl : public CGUIButtonControl
{
public:
  CGUIToggleButtonControl(int parentID, int controlID, float posX, float posY, float width, float height, const CTextureInfo& textureFocus, const CTextureInfo& textureNoFocus, const CTextureInfo& altTextureFocus, const CTextureInfo& altTextureNoFocus, const CLabelInfo &labelInfo);
  virtual ~CGUIToggleButtonControl(void);
  virtual CGUIToggleButtonControl *Clone() const { return new CGUIToggleButtonControl(*this); };

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual bool OnAction(const CAction &action);
  virtual void AllocResources();
  virtual void FreeResources(bool immediately = false);
  virtual void DynamicResourceAlloc(bool bOnOff);
  virtual void SetInvalid();
  virtual void SetPosition(float posX, float posY);
  virtual void SetWidth(float width);
  virtual void SetHeight(float height);
  void SetLabel(const std::string& strLabel);
  void SetAltLabel(const std::string& label);
  virtual CStdString GetDescription() const;
  void SetToggleSelect(const CStdString &toggleSelect);
  void SetAltClickActions(const CGUIAction &clickActions);

protected:
  virtual bool UpdateColors();
  virtual void OnClick();
  CGUIButtonControl m_selectButton;
  unsigned int m_toggleSelect;
};
#endif
