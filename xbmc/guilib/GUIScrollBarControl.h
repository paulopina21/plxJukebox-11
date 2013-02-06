/*!
\file GUIScrollBar.h
\brief
*/

#ifndef GUILIB_GUISCROLLBAR_H
#define GUILIB_GUISCROLLBAR_H

#pragma once



#include "GUITexture.h"
#include "GUIControl.h"

/*!
 \ingroup controls
 \brief
 */
class CGUIScrollBar :
      public CGUIControl
{
public:
  CGUIScrollBar(int parentID, int controlID, float posX, float posY,
                       float width, float height,
                       const CTextureInfo& backGroundTexture,
                       const CTextureInfo& barTexture, const CTextureInfo& barTextureFocus,
                       const CTextureInfo& nibTexture, const CTextureInfo& nibTextureFocus,
                       ORIENTATION orientation, bool showOnePage);
  virtual ~CGUIScrollBar(void);
  virtual CGUIScrollBar *Clone() const { return new CGUIScrollBar(*this); };

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual bool OnAction(const CAction &action);
  virtual void AllocResources();
  virtual void FreeResources(bool immediately = false);
  virtual void DynamicResourceAlloc(bool bOnOff);
  virtual void SetInvalid();
  virtual void SetRange(int pageSize, int numItems);
  virtual bool OnMessage(CGUIMessage& message);
  void SetValue(int value);
  int GetValue() const;
  virtual CStdString GetDescription() const;
  virtual bool IsVisible() const;
protected:
  virtual bool HitTest(const CPoint &point) const;
  virtual EVENT_RESULT OnMouseEvent(const CPoint &point, const CMouseEvent &event);
  virtual bool UpdateColors();
  bool UpdateBarSize();
  bool Move(int iNumSteps);
  virtual void SetFromPosition(const CPoint &point);

  CGUITexture m_guiBackground;
  CGUITexture m_guiBarNoFocus;
  CGUITexture m_guiBarFocus;
  CGUITexture m_guiNibNoFocus;
  CGUITexture m_guiNibFocus;

  int m_numItems;
  int m_pageSize;
  int m_offset;

  bool m_showOnePage;
  ORIENTATION m_orientation;
};
#endif
