#pragma once



#include "guilib/GUIWindow.h"

class CGUIWindowSystemInfo : public CGUIWindow
{
public:
  CGUIWindowSystemInfo(void);
  virtual ~CGUIWindowSystemInfo(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual void FrameMove();
private:
  unsigned int m_section;
  void ResetLabels();
  void SetControlLabel(int id, const char *format, int label, int info);
  std::vector<CStdString> m_diskUsage;
};

