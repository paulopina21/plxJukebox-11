#pragma once



#include "guilib/GUIWindow.h"
#include "threads/CriticalSection.h"
#include "dialogs/GUIDialogSlider.h"

class CGUITextLayout; // forward

class CGUIWindowFullScreen :
      public CGUIWindow, public ISliderCallback
{
public:
  CGUIWindowFullScreen(void);
  virtual ~CGUIWindowFullScreen(void);
  virtual void AllocResources(bool forceLoad = false);
  virtual void FreeResources(bool forceUnLoad = false);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
  virtual void FrameMove();
  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregion);
  virtual void Render();
  virtual void OnWindowLoaded();
  void ChangetheTimeCode(int remote);

  virtual void OnSliderChange(void *data, CGUISliderControl *slider);
protected:
  virtual EVENT_RESULT OnMouseEvent(const CPoint &point, const CMouseEvent &event);

private:
  void RenderTTFSubtitles();
  void SeekChapter(int iChapter);
  void ToggleOSD();

  enum SEEK_TYPE { SEEK_ABSOLUTE, SEEK_RELATIVE };
  enum SEEK_DIRECTION { SEEK_FORWARD, SEEK_BACKWARD };

  /*! \brief Seek to the current time code stamp, either relative or absolute
   \param type - whether the seek is absolute or relative
   \param direction - if relative seeking, which direction to seek
   */
  void SeekToTimeCodeStamp(SEEK_TYPE type, SEEK_DIRECTION direction = SEEK_FORWARD);

  /*! \brief Convert the current timecode into a time in seconds to seek
   */
  double GetTimeCodeStamp();

  /*! \brief pop up a slider dialog for a particular action
   \param action id of the action the slider responds to
   \param label id of the label to display
   \param value value to set on the slider
   \param min minimum value the slider may take
   \param delta change value to advance the slider by with each click
   \param max maximal value the slider may take
   \param modal true if we should wait for the slider to finish. Defaults to false
   */
  void ShowSlider(int action, int label, float value, float min, float delta, float max, bool modal = false);

  bool m_bShowViewModeInfo;
  unsigned int m_dwShowViewModeTimeout;
  CGUIInfoBool m_showCodec;

  bool m_bShowCurrentTime;

  bool m_timeCodeShow;
  unsigned int m_timeCodeTimeout;
  int m_timeCodeStamp[6];
  int m_timeCodePosition;
  
  int m_sliderAction; ///< \brief set to the action id for a slider being displayed \sa ShowSlider

  CCriticalSection m_fontLock;
  CGUITextLayout* m_subsLayout;
};
