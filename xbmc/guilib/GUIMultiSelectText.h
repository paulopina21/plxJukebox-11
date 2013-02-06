#pragma once



#include "GUIButtonControl.h"

/*!
 \ingroup controls
 \brief
 */
class CGUIMultiSelectTextControl : public CGUIControl
{
public:
  CGUIMultiSelectTextControl(int parentID, int controlID,
                    float posX, float posY, float width, float height,
                    const CTextureInfo& textureFocus, const CTextureInfo& textureNoFocus, const CLabelInfo &label, const CGUIInfoLabel &content);

  virtual ~CGUIMultiSelectTextControl(void);
  virtual CGUIMultiSelectTextControl *Clone() const { return new CGUIMultiSelectTextControl(*this); };

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();

  virtual bool OnAction(const CAction &action);
  virtual void OnLeft();
  virtual void OnRight();
  virtual bool HitTest(const CPoint &point) const;
  virtual bool OnMouseOver(const CPoint &point);
  virtual void UpdateInfo(const CGUIListItem *item = NULL);

  virtual CStdString GetDescription() const;
  virtual bool CanFocus() const;

  void UpdateText(const CStdString &text);
  bool MoveLeft();
  bool MoveRight();
  void SelectItemFromPoint(const CPoint &point);
  unsigned int GetFocusedItem() const;
  void SetFocusedItem(unsigned int item);

  // overrides to allow all focus anims to translate down to the focus image
  virtual void SetAnimations(const std::vector<CAnimation> &animations);
  virtual void SetFocus(bool focus);
protected:
  virtual EVENT_RESULT OnMouseEvent(const CPoint &point, const CMouseEvent &event);
  virtual bool UpdateColors();
  void AddString(const CStdString &text, bool selectable, const CStdString &clickAction = "");
  void PositionButtons();
  unsigned int GetNumSelectable() const;
  int GetItemFromPoint(const CPoint &point) const;
  void ScrollToItem(unsigned int item);

  // the static strings and buttons strings
  class CSelectableString
  {
  public:
    CSelectableString(CGUIFont *font, const CStdString &text, bool selectable, const CStdString &clickAction);
    CGUITextLayout m_text;
    float m_length;
    bool m_selectable;
    CStdString m_clickAction;
  };
  std::vector<CSelectableString> m_items;

  CLabelInfo m_label;
  CGUIInfoLabel  m_info;
  CStdString m_oldText;
  unsigned int m_renderTime;

  // scrolling
  float        m_totalWidth;
  float        m_offset;
  float        m_scrollOffset;
  float        m_scrollSpeed;
  unsigned int m_scrollLastTime;

  // buttons
  CGUIButtonControl m_button;
  unsigned int m_selectedItem;
  std::vector<CGUIButtonControl> m_buttons;
};

