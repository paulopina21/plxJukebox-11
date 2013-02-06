#pragma once



#include "guilib/GUIDialog.h"
#include "XBDateTime.h"

class CGUIDialogSeekBar : public CGUIDialog
{
public:
  CGUIDialogSeekBar(void);
  virtual ~CGUIDialogSeekBar(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
  virtual void FrameMove();
  void ResetTimer();
  float GetPercentage() {return m_fSeekPercentage;};
  CStdString GetSeekTimeLabel(TIME_FORMAT format = TIME_FORMAT_GUESS);
protected:
  unsigned int m_timer;
  float m_fSeekPercentage;
  bool m_bRequireSeek;
};
