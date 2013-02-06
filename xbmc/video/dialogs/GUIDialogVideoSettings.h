#pragma once



#include "settings/GUIDialogSettings.h"

class CGUIDialogVideoSettings :
      public CGUIDialogSettings
{
public:
  CGUIDialogVideoSettings(void);
  virtual ~CGUIDialogVideoSettings(void);

  static CStdString FormatInteger(float value, float minimum);
  static CStdString FormatFloat(float value, float minimum);

protected:
  virtual void CreateSettings();
  virtual void OnSettingChanged(SettingInfo &setting);
};

