#pragma once



#include "GUIViewState.h"

class CGUIViewStateWindowPictures : public CGUIViewState
{
public:
  CGUIViewStateWindowPictures(const CFileItemList& items);

protected:
  virtual void SaveViewState();
  virtual CStdString GetLockType();
  virtual CStdString GetExtensions();
  virtual VECSOURCES& GetSources();
};

