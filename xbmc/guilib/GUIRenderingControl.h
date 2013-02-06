#pragma once


#include "GUIControl.h"
#include "addons/IAddon.h"

class CGUIRenderingControl : public CGUIControl
{
public:
  CGUIRenderingControl(int parentID, int controlID, float posX, float posY, float width, float height);
  CGUIRenderingControl(const CGUIRenderingControl &from);
  virtual CGUIRenderingControl *Clone() const { return new CGUIRenderingControl(*this); }; //TODO check for naughties

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual void UpdateVisibility(const CGUIListItem *item = NULL);
  virtual void FreeResources(bool immediately = false);
  virtual bool CanFocus() const { return false; }
  virtual bool CanFocusFromPoint(const CPoint &point) const;
  void LoadAddon(const ADDON::AddonPtr &addon);

protected:
  CCriticalSection m_rendering;
  ADDON::VizPtr m_addon;
};
