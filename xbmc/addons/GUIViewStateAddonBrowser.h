#pragma once



#include "GUIViewState.h"

class CGUIViewStateAddonBrowser : public CGUIViewState
{
public:
  CGUIViewStateAddonBrowser(const CFileItemList& items);

protected:
  virtual void SaveViewState();
  virtual CStdString GetExtensions();
  virtual VECSOURCES& GetSources();
};

