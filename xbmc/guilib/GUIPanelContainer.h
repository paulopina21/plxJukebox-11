/*!
\file GUIPanelContainer.h
\brief
*/

#pragma once



#include "GUIBaseContainer.h"

/*!
 \ingroup controls
 \brief
 */
class CGUIPanelContainer : public CGUIBaseContainer
{
public:
  CGUIPanelContainer(int parentID, int controlID, float posX, float posY, float width, float height, ORIENTATION orientation, const CScroller& scroller, int preloadItems);
  virtual ~CGUIPanelContainer(void);
  virtual CGUIPanelContainer *Clone() const { return new CGUIPanelContainer(*this); };

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual bool OnAction(const CAction &action);
  virtual bool OnMessage(CGUIMessage& message);
  virtual void OnLeft();
  virtual void OnRight();
  virtual void OnUp();
  virtual void OnDown();
  virtual bool GetCondition(int condition, int data) const;
protected:
  virtual bool MoveUp(bool wrapAround);
  virtual bool MoveDown(bool wrapAround);
  virtual bool MoveLeft(bool wrapAround);
  virtual bool MoveRight(bool wrapAround);
  virtual void Scroll(int amount);
  float AnalogScrollSpeed() const;
  virtual void ValidateOffset();
  virtual void CalculateLayout();
  unsigned int GetRows() const;
  virtual int  CorrectOffset(int offset, int cursor) const;
  virtual bool SelectItemFromPoint(const CPoint &point);
  virtual int GetCursorFromPoint(const CPoint &point, CPoint *itemPoint = NULL) const;
  void SetCursor(int cursor);
  virtual void SelectItem(int item);
  virtual bool HasPreviousPage() const;
  virtual bool HasNextPage() const;

  int m_itemsPerRow;
};

