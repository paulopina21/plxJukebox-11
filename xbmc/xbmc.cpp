// XBMC
//
// libraries:
//   - CDRipX   : doesnt support section loading yet
//   - xbfilezilla : doesnt support section loading yet
//

#include "system.h"
#include "settings/AppParamParser.h"
#include "settings/AdvancedSettings.h"
#include "FileItem.h"
#include "Application.h"
#include "PlayListPlayer.h"
#include "utils/log.h"
#ifdef _LINUX
#include <sys/resource.h>
#include <signal.h>
#endif
#ifdef __APPLE__
#include "Util.h"
#endif
#ifdef HAS_LIRC
#include "input/linux/LIRC.h"
#endif

#ifdef IS_JUKEBOX // Laureon: Jukebox HardLock System
#ifdef __cplusplus 
extern "C" {
#endif
int C500(unsigned char *);

#ifdef __cplusplus
}
#endif
#endif


int main(int argc, char* argv[])
{
  int status = -1;
  //this can't be set from CAdvancedSettings::Initialize() because it will overwrite
  //the loglevel set with the --debug flag
#ifdef _DEBUG
  g_advancedSettings.m_logLevel     = LOG_LEVEL_DEBUG;
  g_advancedSettings.m_logLevelHint = LOG_LEVEL_DEBUG;
#else
  g_advancedSettings.m_logLevel     = LOG_LEVEL_NORMAL;
  g_advancedSettings.m_logLevelHint = LOG_LEVEL_NORMAL;
#endif
  CLog::SetLogLevel(g_advancedSettings.m_logLevel);

  // Laureon: Jukebox HardLock System
  #ifdef IS_JUKEBOX
    int   state = 0;
    BYTE  pass[10];// "11O25WH11"

    BYTE  *buffer;
    BYTE  crossBuffer[1000];

    state = 0;
    buffer = crossBuffer;
    crossBuffer[10] = '\0';
    pass[9] = '\0';

    strcpy((char *)pass, "11O25WH11");

    for (int n = 0; n < 9; n++) crossBuffer[n + 1] = pass[n];

    crossBuffer[0]  = 3;  // Le ID

    buffer = crossBuffer;
//    state = C500(buffer);

//    if (state != 0) {
//      fprintf(stderr, "ERRO 101");
//      return -1;
//    }

  #endif


#ifdef _LINUX
#if defined(DEBUG)
  struct rlimit rlim;
  rlim.rlim_cur = rlim.rlim_max = RLIM_INFINITY;
  if (setrlimit(RLIMIT_CORE, &rlim) == -1)
    CLog::Log(LOGDEBUG, "Failed to set core size limit (%s)", strerror(errno));
#endif
  // Prevent child processes from becoming zombies on exit if not waited upon. See also Util::Command
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));

  sa.sa_flags = SA_NOCLDWAIT;
  sa.sa_handler = SIG_IGN;
  sigaction(SIGCHLD, &sa, NULL);
#endif
  setlocale(LC_NUMERIC, "C");
  g_advancedSettings.Initialize();
  
#ifndef _WIN32
  CAppParamParser appParamParser;
  appParamParser.Parse((const char **)argv, argc);
#endif
  g_application.Preflight();
  if (!g_application.Create())
  {
    fprintf(stderr, "ERROR: Unable to create application. Exiting\n");
    return status;
  }

  try
  {
    status = g_application.Run();
  }
  catch(...)
  {
    fprintf(stderr, "ERROR: Exception caught on main loop. Exiting\n");
    status = -1;
  }

  return status;
}
