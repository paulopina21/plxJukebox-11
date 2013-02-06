#pragma once



#include "guilib/GUIWindow.h"

class CKaraokeLyrics;
class CKaraokeWindowBackground;


class CGUIWindowKaraokeLyrics : public CGUIWindow
{
public:
  CGUIWindowKaraokeLyrics(void);
  virtual ~CGUIWindowKaraokeLyrics(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
  virtual void Render();

  void    newSong( CKaraokeLyrics * lyrics );
  void    pauseSong( bool now_paused );
  void    stopSong();

protected:

  //! Critical section protects this class from requests from different threads
  CCriticalSection   m_CritSection;

  //! Pointer to karaoke lyrics renderer
  CKaraokeLyrics  *  m_Lyrics;

  //! Pointer to background object
  CKaraokeWindowBackground * m_Background;
};
