

#include "GUIToggleButtonControl.h"
#include "GUIWindowManager.h"
#include "GUIDialog.h"
#include "utils/CharsetConverter.h"
#include "GUIInfoManager.h"

using namespace std;

CGUIToggleButtonControl::CGUIToggleButtonControl(int parentID, int controlID, float posX, float posY, float width, float height, const CTextureInfo& textureFocus, const CTextureInfo& textureNoFocus, const CTextureInfo& altTextureFocus, const CTextureInfo& altTextureNoFocus, const CLabelInfo &labelInfo)
    : CGUIButtonControl(parentID, controlID, posX, posY, width, height, textureFocus, textureNoFocus, labelInfo)
    , m_selectButton(parentID, controlID, posX, posY, width, height, altTextureFocus, altTextureNoFocus, labelInfo)
{
  m_toggleSelect = 0;
  ControlType = GUICONTROL_TOGGLEBUTTON;
}

CGUIToggleButtonControl::~CGUIToggleButtonControl(void)
{
}

void CGUIToggleButtonControl::Process(unsigned int currentTime, CDirtyRegionList &dirtyregions)
{
  // ask our infoManager whether we are selected or not...
  bool selected = m_bSelected;
  if (m_toggleSelect)
    selected = g_infoManager.GetBoolValue(m_toggleSelect);
  if (selected != m_bSelected)
  {
    MarkDirtyRegion();
    m_bSelected = selected;
  }

  if (m_bSelected)
  {
    // render our Alternate textures...
    m_selectButton.SetFocus(HasFocus());
    m_selectButton.SetVisible(IsVisible());
    m_selectButton.SetEnabled(!IsDisabled());
    m_selectButton.SetPulseOnSelect(m_pulseOnSelect);
    m_selectButton.DoProcess(currentTime, dirtyregions);
  }
  CGUIButtonControl::Process(currentTime, dirtyregions);
}

void CGUIToggleButtonControl::Render()
{
  if (m_bSelected)
  {
    m_selectButton.Render();
    CGUIControl::Render();
  }
  else
  { // render our Normal textures...
    CGUIButtonControl::Render();
  }
}

bool CGUIToggleButtonControl::OnAction(const CAction &action)
{
  if (action.GetID() == ACTION_SELECT_ITEM)
  {
    m_bSelected = !m_bSelected;
    SetInvalid();
  }
  return CGUIButtonControl::OnAction(action);
}

void CGUIToggleButtonControl::AllocResources()
{
  CGUIButtonControl::AllocResources();
  m_selectButton.AllocResources();
}

void CGUIToggleButtonControl::FreeResources(bool immediately)
{
  CGUIButtonControl::FreeResources(immediately);
  m_selectButton.FreeResources(immediately);
}

void CGUIToggleButtonControl::DynamicResourceAlloc(bool bOnOff)
{
  CGUIButtonControl::DynamicResourceAlloc(bOnOff);
  m_selectButton.DynamicResourceAlloc(bOnOff);
}

void CGUIToggleButtonControl::SetInvalid()
{
  CGUIButtonControl::SetInvalid();
  m_selectButton.SetInvalid();
}

void CGUIToggleButtonControl::SetPosition(float posX, float posY)
{
  CGUIButtonControl::SetPosition(posX, posY);
  m_selectButton.SetPosition(posX, posY);
}

void CGUIToggleButtonControl::SetWidth(float width)
{
  CGUIButtonControl::SetWidth(width);
  m_selectButton.SetWidth(width);
}

void CGUIToggleButtonControl::SetHeight(float height)
{
  CGUIButtonControl::SetHeight(height);
  m_selectButton.SetHeight(height);
}

bool CGUIToggleButtonControl::UpdateColors()
{
  bool changed = CGUIButtonControl::UpdateColors();
  changed |= m_selectButton.SetColorDiffuse(m_diffuseColor);
  changed |= m_selectButton.UpdateColors();

  return changed;
}

void CGUIToggleButtonControl::SetLabel(const string &strLabel)
{
  CGUIButtonControl::SetLabel(strLabel);
  m_selectButton.SetLabel(strLabel);
}

void CGUIToggleButtonControl::SetAltLabel(const string &label)
{
  if (label.size())
    m_selectButton.SetLabel(label);
}

CStdString CGUIToggleButtonControl::GetDescription() const
{
  if (m_bSelected)
    return m_selectButton.GetDescription();
  return CGUIButtonControl::GetDescription();
}

void CGUIToggleButtonControl::SetAltClickActions(const CGUIAction &clickActions)
{
  m_selectButton.SetClickActions(clickActions);
}

void CGUIToggleButtonControl::OnClick()
{
  // the ! is here as m_bSelected gets updated before this is called
  if (!m_bSelected && m_selectButton.HasClickActions())
    m_selectButton.OnClick();
  else
    CGUIButtonControl::OnClick();
}

void CGUIToggleButtonControl::SetToggleSelect(const CStdString &toggleSelect)
{
  m_toggleSelect = g_infoManager.Register(toggleSelect, GetParentID());
}
