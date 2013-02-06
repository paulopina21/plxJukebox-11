/*!
\file GUIListGroup.h
\brief
*/

#pragma once



#include "GUIControlGroup.h"

/*!
 \ingroup controls
 \brief a group of controls within a list/panel container
 */
class CGUIListGroup : public CGUIControlGroup
{
public:
  CGUIListGroup(int parentID, int controlID, float posX, float posY, float width, float height);
  CGUIListGroup(const CGUIListGroup &right);
  virtual ~CGUIListGroup(void);
  virtual CGUIListGroup *Clone() const { return new CGUIListGroup(*this); };

  virtual void AddControl(CGUIControl *control, int position = -1);

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void ResetAnimation(ANIMATION_TYPE type);
  virtual void UpdateVisibility(const CGUIListItem *item = NULL);
  virtual void UpdateInfo(const CGUIListItem *item);
  virtual void SetInvalid();

  void SetFocusedItem(unsigned int subfocus);
  unsigned int GetFocusedItem() const;
  bool MoveLeft();
  bool MoveRight();
  void SetState(bool selected, bool focused);
  void SelectItemFromPoint(const CPoint &point);

protected:
  const CGUIListItem *m_item;
};

