#pragma once



#include "guilib/GUIWindow.h"
#include "utils/Stopwatch.h"

class CGUIWindowWeather : public CGUIWindow
{
public:
  CGUIWindowWeather(void);
  virtual ~CGUIWindowWeather(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual void FrameMove();

protected:
  virtual void OnInitWindow();

  void UpdateButtons();
  void UpdateLocations();
  void SetProperties();
  void ClearProperties();
  void SetLocation(int loc);

  unsigned int m_maxLocation;
};
