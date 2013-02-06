/*!
\file GUISliderControl.h
\brief
*/

#ifndef GUILIB_GUISLIDERCONTROL_H
#define GUILIB_GUISLIDERCONTROL_H

#pragma once



#include "GUIControl.h"
#include "GUITexture.h"

#define SPIN_CONTROL_TYPE_INT       1
#define SPIN_CONTROL_TYPE_FLOAT     2
#define SPIN_CONTROL_TYPE_TEXT      3

typedef struct
{
  const char *action;
  const char *formatString;
  int         infoCode;
  bool        fireOnDrag;
} SliderAction;

/*!
 \ingroup controls
 \brief
 */
class CGUISliderControl :
      public CGUIControl
{
public:
  CGUISliderControl(int parentID, int controlID, float posX, float posY, float width, float height, const CTextureInfo& backGroundTexture, const CTextureInfo& mibTexture, const CTextureInfo& nibTextureFocus, int iType);
  virtual ~CGUISliderControl(void);
  virtual CGUISliderControl *Clone() const { return new CGUISliderControl(*this); };

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual bool OnAction(const CAction &action);
  virtual void AllocResources();
  virtual void FreeResources(bool immediately = false);
  virtual void DynamicResourceAlloc(bool bOnOff);
  virtual void SetInvalid();
  virtual void SetRange(int iStart, int iEnd);
  virtual void SetFloatRange(float fStart, float fEnd);
  virtual bool OnMessage(CGUIMessage& message);
  void SetInfo(int iInfo);
  void SetPercentage(int iPercent);
  int GetPercentage() const;
  void SetIntValue(int iValue);
  int GetIntValue() const;
  void SetFloatValue(float fValue);
  float GetFloatValue() const;
  void SetIntInterval(int iInterval);
  void SetFloatInterval(float fInterval);
  void SetType(int iType) { m_iType = iType; };
  virtual CStdString GetDescription() const;
  void SetTextValue(const CStdString &textValue) { m_textValue = textValue; };
  void SetAction(const CStdString &action);
protected:
  virtual bool HitTest(const CPoint &point) const;
  virtual EVENT_RESULT OnMouseEvent(const CPoint &point, const CMouseEvent &event);
  virtual bool UpdateColors();
  virtual void Move(int iNumSteps);
  virtual void SetFromPosition(const CPoint &point);
  /*! \brief Get the current position of the slider as a proportion
   \return slider position in the range [0,1]
   */
  float GetProportion() const;
  
  /*! \brief Send a click message (and/or action) to the app in response to a slider move
   */
  void SendClick();

  CGUITexture m_guiBackground;
  CGUITexture m_guiMid;
  CGUITexture m_guiMidFocus;
  int m_iType;

  int m_iPercent;

  int m_iValue;
  int m_iStart;
  int m_iInterval;
  int m_iEnd;

  float m_fValue;
  float m_fStart;
  float m_fInterval;
  float m_fEnd;

  int m_iInfoCode;
  CStdString m_textValue; ///< Allows overriding of the text value to be displayed (parent must update when the slider updates)
  const SliderAction *m_action; ///< Allows the skin to configure the action of a click on the slider \sa SendClick
  bool m_dragging; ///< Whether we're in a (mouse/touch) drag operation or not - some actions are sent only on release.
};
#endif
