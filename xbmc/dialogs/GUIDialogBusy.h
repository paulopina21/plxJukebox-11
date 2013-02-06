#pragma once



#include "guilib/GUIDialog.h"


class CGUIDialogBusy: public CGUIDialog
{
public:
  CGUIDialogBusy(void);
  virtual ~CGUIDialogBusy(void);
  virtual bool OnBack(int actionID);
  virtual void DoProcess(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();

  bool IsCanceled() { return m_bCanceled; }
protected:
  virtual void Show_Internal(); // modeless'ish
  bool m_bCanceled;
  bool m_bLastVisible;
};
