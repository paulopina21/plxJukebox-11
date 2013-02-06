#pragma once



#include "guilib/GUIWindow.h"

class CGUIWindowSettingsScreenCalibration : public CGUIWindow
{
public:
  CGUIWindowSettingsScreenCalibration(void);
  virtual ~CGUIWindowSettingsScreenCalibration(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
  virtual void DoProcess(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void FrameMove();
  virtual void DoRender();
  virtual void AllocResources(bool forceLoad = false);
  virtual void FreeResources(bool forceUnLoad = false);

protected:
  unsigned int FindCurrentResolution();
  void NextControl();
  void ResetControls();
  void EnableControl(int iControl);
  void UpdateFromControl(int iControl);
  UINT m_iCurRes;
  std::vector<RESOLUTION> m_Res;
  int m_iControl;
  float m_fPixelRatioBoxHeight;
};
