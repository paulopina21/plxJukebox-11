#pragma once


#include "guilib/GUIDialog.h"
#include "GUIViewControl.h"

namespace PERIPHERALS
{
  class CGUIDialogPeripheralManager : public CGUIDialog
  {
  public:
    CGUIDialogPeripheralManager(void);
    virtual ~CGUIDialogPeripheralManager(void);
    virtual bool OnMessage(CGUIMessage& message);
    virtual bool OnAction(const CAction& action);
    virtual void OnWindowLoaded(void);
    virtual void OnWindowUnload(void);
    virtual bool HasListItems() const { return true; };
    virtual CFileItemPtr GetCurrentListItem(void) const;
    virtual void Update(void);

  protected:
    virtual bool OnMessageInit(CGUIMessage &message);
    virtual bool OnMessageClick(CGUIMessage &message);

    virtual bool OnClickList(CGUIMessage &message);
    virtual bool OnClickButtonClose(CGUIMessage &message);
    virtual bool OnClickButtonSettings(CGUIMessage &message);
    virtual bool OpenSettingsDialog(void);
    virtual bool CurrentItemHasSettings(void) const;

  private:
    void Clear(void);
    void UpdateButtons(void);

    int             m_iSelected;
    CFileItemList*  m_peripheralItems;
    CGUIViewControl m_viewControl;
  };
}
