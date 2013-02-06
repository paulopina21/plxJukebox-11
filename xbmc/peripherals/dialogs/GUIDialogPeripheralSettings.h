#pragma once


#include "guilib/GUIDialog.h"
#include "settings/GUIDialogSettings.h"
#include "FileItem.h"

namespace PERIPHERALS
{
  class CGUIDialogPeripheralSettings : public CGUIDialogSettings
  {
  public:
    CGUIDialogPeripheralSettings(void);
    virtual ~CGUIDialogPeripheralSettings(void);

    virtual void SetFileItem(CFileItemPtr item);
    virtual bool OnMessage(CGUIMessage &message);
  protected:
    virtual void CreateSettings();
    virtual void OnOkay(void);
    virtual void ResetDefaultSettings(void);
    virtual void UpdatePeripheralSettings(void);

    CFileItem *                      m_item;
    bool                             m_bIsInitialising;
    std::map<CStdString, bool>       m_boolSettings;
    std::map<CStdString, float>      m_intSettings;
    std::map<CStdString, float>      m_floatSettings;
    std::map<CStdString, CStdString> m_stringSettings;
  };
}
