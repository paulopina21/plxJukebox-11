#pragma once



#include "guilib/GUIWindow.h"
#ifdef HAS_SCREENSAVER
#include "addons/ScreenSaver.h"
#endif

#include "threads/CriticalSection.h"

#define SCREENSAVER_FADE   1
#define SCREENSAVER_BLACK  2
#define SCREENSAVER_XBS    3

class CGUIWindowScreensaver : public CGUIWindow
{
public:
  CGUIWindowScreensaver(void);
  virtual ~CGUIWindowScreensaver(void);

  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
  virtual void Render();
  virtual void Process(unsigned int currentTime, CDirtyRegionList &regions);

protected:
  virtual EVENT_RESULT OnMouseEvent(const CPoint &point, const CMouseEvent &event);

private:
  bool m_bInitialized;
  CCriticalSection m_critSection;
#ifdef HAS_SCREENSAVER
  boost::shared_ptr<ADDON::CScreenSaver> m_addon;
#endif
};
