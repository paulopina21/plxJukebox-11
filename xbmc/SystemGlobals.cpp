
#include "system.h"
#include "cores/VideoRenderers/RenderManager.h"
#include "input/MouseStat.h"
#include "Application.h"
#include "GUILargeTextureManager.h"
#include "guilib/TextureManager.h"
#include "guilib/AudioContext.h"
#include "settings/GUISettings.h"
#include "settings/Settings.h"
#include "utils/AlarmClock.h"
#include "utils/DownloadQueueManager.h"
#include "GUIInfoManager.h"
#include "filesystem/DllLibCurl.h"
#include "filesystem/DirectoryCache.h"
#include "GUIPassword.h"
#include "LangInfo.h"
#include "utils/LangCodeExpander.h"
#include "PartyModeManager.h"
#include "PlayListPlayer.h"
#include "guilib/LocalizeStrings.h"
#include "guilib/GUIWindowManager.h"
#ifdef HAS_PYTHON
#include "interfaces/python/XBPython.h"
#endif

#ifdef IS_JUKEBOX
#include "jukebox/JukeboxManager.h"
#include "filesystem/PFCManager.h"
#endif

  CGUISettings       g_guiSettings;
  CSettings          g_settings;

  CXBMCRenderManager g_renderManager;
  CAudioContext      g_audioContext;
  CLangInfo          g_langInfo;
  CLangCodeExpander  g_LangCodeExpander;
  CLocalizeStrings   g_localizeStrings;
  CLocalizeStrings   g_localizeStringsTemp;

  CGUIWindowManager  g_windowManager;
  XFILE::CDirectoryCache g_directoryCache;

  CGUITextureManager g_TextureManager;
  CGUILargeTextureManager g_largeTextureManager;
  CMouseStat         g_Mouse;
  CGUIPassword       g_passwordManager;
  CGUIInfoManager    g_infoManager;

  XCURL::DllLibCurlGlobal g_curlInterface;
  CDownloadQueueManager g_DownloadManager;
  CPartyModeManager     g_partyModeManager;

#ifdef HAS_PYTHON
  XBPython           g_pythonParser;
#endif
  CAlarmClock        g_alarmClock;
  PLAYLIST::CPlayListPlayer g_playlistPlayer;
  CApplication       g_application;
#ifdef IS_JUKEBOX
  CJukeboxManager   g_jukeboxManager;
  //CPFCManager         g_PFCManager;
#endif
