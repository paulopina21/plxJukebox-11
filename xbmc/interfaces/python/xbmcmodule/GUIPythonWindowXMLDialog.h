#pragma once



#include "GUIPythonWindowXML.h"

class CApplicationMessenger;

class CGUIPythonWindowXMLDialog : public CGUIPythonWindowXML
{
  public:
    CGUIPythonWindowXMLDialog(int id, CStdString strXML, CStdString strFallBackPath);
    virtual ~CGUIPythonWindowXMLDialog(void);
    virtual bool    OnMessage(CGUIMessage &message);
    virtual bool    IsDialogRunning() const { return m_active; }
    virtual bool    IsDialog() const { return true;};
    virtual bool    IsModalDialog() const { return true; };
    virtual bool    IsMediaWindow() const { return false; };
  protected:
    friend class CApplicationMessenger;
    void Show_Internal(bool show = true);
    virtual void OnDeinitWindow(int nextWindowID = 0);
};

