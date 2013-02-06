/*!
\file GUIVideoControl.h
\brief
*/

#ifndef GUILIB_GUIVIDEOCONTROL_H
#define GUILIB_GUIVIDEOCONTROL_H

#pragma once



#include "GUIControl.h"

/*!
 \ingroup controls
 \brief
 */
class CGUIVideoControl :
      public CGUIControl
{
public:
  CGUIVideoControl(int parentID, int controlID, float posX, float posY, float width, float height);
  virtual ~CGUIVideoControl(void);
  virtual CGUIVideoControl *Clone() const { return new CGUIVideoControl(*this); };

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual EVENT_RESULT OnMouseEvent(const CPoint &point, const CMouseEvent &event);
  virtual bool CanFocus() const;
  virtual bool CanFocusFromPoint(const CPoint &point) const;
};
#endif
