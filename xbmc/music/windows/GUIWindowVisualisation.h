#pragma once



#include "guilib/GUIWindow.h"
#include "music/tags/MusicInfoTag.h"
#include "utils/Stopwatch.h"

class CGUIWindowVisualisation :
      public CGUIWindow
{
public:
  CGUIWindowVisualisation(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
  virtual void FrameMove();
protected:
  virtual EVENT_RESULT OnMouseEvent(const CPoint &point, const CMouseEvent &event);

  CStopWatch m_initTimer;
  CStopWatch m_lockedTimer;
  bool m_bShowPreset;
  MUSIC_INFO::CMusicInfoTag m_tag;    // current tag info, for finding when the info manager updates
};

