#pragma once



#include "threads/CriticalSection.h"
#include "utils/log.h"
#include "utils/StdString.h"

#include <map>

// forward definitions
class CAction;
class CGUISound;
class TiXmlNode;

enum WINDOW_SOUND { SOUND_INIT = 0, SOUND_DEINIT };

class CGUIAudioManager
{
  class CWindowSounds
  {
  public:
    CStdString strInitFile;
    CStdString strDeInitFile;
  };

public:
  CGUIAudioManager();
          ~CGUIAudioManager();

          void        Initialize(int iDevice);
          void        DeInitialize(int iDevice);

          bool        Load();

          void        PlayActionSound(const CAction& action);
          void        PlayWindowSound(int id, WINDOW_SOUND event);
          void        PlayPythonSound(const CStdString& strFileName);

          void        FreeUnused();

          void        Enable(bool bEnable);
          void        SetVolume(int iLevel);
          void        Stop();
private:
          bool        LoadWindowSound(TiXmlNode* pWindowNode, const CStdString& strIdentifier, CStdString& strFile);

  typedef std::map<int, CStdString> actionSoundMap;
  typedef std::map<int, CWindowSounds> windowSoundMap;

  typedef std::map<CStdString, CGUISound*> pythonSoundsMap;
  typedef std::map<int, CGUISound*> windowSoundsMap;

  actionSoundMap      m_actionSoundMap;
  windowSoundMap      m_windowSoundMap;

  CGUISound*          m_actionSound;
  windowSoundsMap     m_windowSounds;
  pythonSoundsMap     m_pythonSounds;

  CStdString          m_strMediaDir;
  bool                m_bInitialized;
  bool                m_bEnabled;

  CCriticalSection    m_cs;
};

extern CGUIAudioManager g_audioManager;
