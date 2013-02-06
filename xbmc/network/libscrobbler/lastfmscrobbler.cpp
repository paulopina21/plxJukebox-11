

#include "lastfmscrobbler.h"
#include "threads/Atomics.h"
#include "settings/GUISettings.h"
#include "settings/Settings.h"
#include "utils/URIUtils.h"
#include "guilib/LocalizeStrings.h"
#include "dialogs/GUIDialogKaiToast.h"

long CLastfmScrobbler::m_instanceLock = 0;
CLastfmScrobbler *CLastfmScrobbler::m_pInstance = NULL;

CLastfmScrobbler::CLastfmScrobbler()
  : CScrobbler(LASTFM_SCROBBLER_HANDSHAKE_URL, LASTFM_SCROBBLER_LOG_PREFIX)
{
}

CLastfmScrobbler::~CLastfmScrobbler()
{
  Term();
}

CLastfmScrobbler *CLastfmScrobbler::GetInstance()
{
  if (!m_pInstance) // Avoid spinning aimlessly
  {
    CAtomicSpinLock lock(m_instanceLock);
    if (!m_pInstance)
    {
      m_pInstance = new CLastfmScrobbler;
    }
  }
  return m_pInstance;
}

void CLastfmScrobbler::RemoveInstance()
{
  if (m_pInstance)
  {
    CAtomicSpinLock lock(m_instanceLock);
    delete m_pInstance;
    m_pInstance = NULL;
  }
}

void CLastfmScrobbler::LoadCredentials()
{
  SetUsername(g_guiSettings.GetString("scrobbler.lastfmusername"));
  SetPassword(g_guiSettings.GetString("scrobbler.lastfmpass"));
}

CStdString CLastfmScrobbler::GetJournalFileName()
{
  CStdString strFileName = g_settings.GetProfileUserDataFolder();
  return URIUtils::AddFileToFolder(strFileName, "LastfmScrobbler.xml");
}

void CLastfmScrobbler::NotifyUser(int error)
{
  CStdString strText;
  CStdString strAudioScrobbler;
  switch (error)
  {
    case SCROBBLER_USER_ERROR_BADAUTH:
      strText = g_localizeStrings.Get(15206);
      m_bBadAuth = true;
      strAudioScrobbler = g_localizeStrings.Get(15200);  // AudioScrobbler
      CGUIDialogKaiToast::QueueNotification(CGUIDialogKaiToast::Error, strAudioScrobbler, strText, 10000);
      break;
    case SCROBBLER_USER_ERROR_BANNED:
      strText = g_localizeStrings.Get(15205);
      m_bBanned = true;
      strAudioScrobbler = g_localizeStrings.Get(15200);  // AudioScrobbler
      CGUIDialogKaiToast::QueueNotification(CGUIDialogKaiToast::Error, strAudioScrobbler, strText, 10000);
      break;
    default:
      break;
  }
}

bool CLastfmScrobbler::CanScrobble()
{
  return (!g_guiSettings.GetString("scrobbler.lastfmusername").IsEmpty()  &&
          !g_guiSettings.GetString("scrobbler.lastfmpass").IsEmpty()  &&
         (g_guiSettings.GetBool("scrobbler.lastfmsubmit") ||
          g_guiSettings.GetBool("scrobbler.lastfmsubmitradio")));
}

