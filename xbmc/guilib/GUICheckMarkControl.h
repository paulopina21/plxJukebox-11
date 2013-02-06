/*!
\file GUICheckMarkControl.h
\brief
*/

#ifndef CGUILIB_GUICHECKMARK_CONTROL_H
#define CGUILIB_GUICHECKMARK_CONTROL_H

#pragma once



#include "GUITexture.h"
#include "GUILabel.h"
#include "GUIControl.h"

/*!
 \ingroup controls
 \brief
 */
class CGUICheckMarkControl: public CGUIControl
{
public:
  CGUICheckMarkControl(int parentID, int controlID, float posX, float posY, float width, float height, const CTextureInfo& textureCheckMark, const CTextureInfo& textureCheckMarkNF, float checkWidth, float checkHeight, const CLabelInfo &labelInfo);
  virtual ~CGUICheckMarkControl(void);
  virtual CGUICheckMarkControl *Clone() const { return new CGUICheckMarkControl(*this); };

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual bool OnAction(const CAction &action) ;
  virtual bool OnMessage(CGUIMessage& message);
  virtual void AllocResources();
  virtual void FreeResources(bool immediately = false);
  virtual void DynamicResourceAlloc(bool bOnOff);
  virtual void SetInvalid();

  void SetLabel(const std::string& strLabel);
  const std::string GetLabel() const { return m_strLabel; };
  const CLabelInfo& GetLabelInfo() const { return m_label.GetLabelInfo(); };
  void SetSelected(bool bOnOff);
  bool GetSelected() const;

  void PythonSetLabel(const CStdString &strFont, const std::string &strText, color_t textColor);
  void PythonSetDisabledColor(color_t disabledColor);

protected:
  virtual EVENT_RESULT OnMouseEvent(const CPoint &point, const CMouseEvent &event);
  virtual bool UpdateColors();
  CGUILabel::COLOR GetTextColor() const;
  
  CGUITexture m_imgCheckMark;
  CGUITexture m_imgCheckMarkNoFocus;

  CGUILabel  m_label;
  std::string m_strLabel;
  bool m_bSelected;
};
#endif
