

#include "librefmscrobbler.h"
#include "threads/Atomics.h"
#include "settings/GUISettings.h"
#include "settings/Settings.h"
#include "utils/URIUtils.h"
#include "guilib/LocalizeStrings.h"
#include "dialogs/GUIDialogKaiToast.h"

long CLibrefmScrobbler::m_instanceLock = 0;
CLibrefmScrobbler *CLibrefmScrobbler::m_pInstance = NULL;

CLibrefmScrobbler::CLibrefmScrobbler()
  : CScrobbler(LIBREFM_SCROBBLER_HANDSHAKE_URL, LIBREFM_SCROBBLER_LOG_PREFIX)
{
}

CLibrefmScrobbler::~CLibrefmScrobbler()
{
  Term();
}

CLibrefmScrobbler *CLibrefmScrobbler::GetInstance()
{
  if (!m_pInstance) // Avoid spinning aimlessly
  {
    CAtomicSpinLock lock(m_instanceLock);
    if (!m_pInstance)
    {
      m_pInstance = new CLibrefmScrobbler;
    }
  }
  return m_pInstance;
}

void CLibrefmScrobbler::RemoveInstance()
{
  if (m_pInstance)
  {
    CAtomicSpinLock lock(m_instanceLock);
    delete m_pInstance;
    m_pInstance = NULL;
  }
}

void CLibrefmScrobbler::LoadCredentials()
{
  SetUsername(g_guiSettings.GetString("scrobbler.librefmusername"));
  SetPassword(g_guiSettings.GetString("scrobbler.librefmpass"));
}

CStdString CLibrefmScrobbler::GetJournalFileName()
{
  CStdString strFileName = g_settings.GetProfileUserDataFolder();
  return URIUtils::AddFileToFolder(strFileName, "LibrefmScrobbler.xml");
}

void CLibrefmScrobbler::NotifyUser(int error)
{
  CStdString strText;
  CStdString strAudioScrobbler;
  switch (error)
  {
    case SCROBBLER_USER_ERROR_BADAUTH:
      strText = g_localizeStrings.Get(15206);
      m_bBadAuth = true;
      strAudioScrobbler = g_localizeStrings.Get(15220);  // Libre.fm
      CGUIDialogKaiToast::QueueNotification(CGUIDialogKaiToast::Error, strAudioScrobbler, strText, 10000);
      break;
    case SCROBBLER_USER_ERROR_BANNED:
      strText = g_localizeStrings.Get(15205);
      m_bBanned = true;
      strAudioScrobbler = g_localizeStrings.Get(15220);  // Libre.fm
      CGUIDialogKaiToast::QueueNotification(CGUIDialogKaiToast::Error, strAudioScrobbler, strText, 10000);
      break;
    default:
      break;
  }
}

bool CLibrefmScrobbler::CanScrobble()
{
  return (!g_guiSettings.GetString("scrobbler.librefmusername").IsEmpty()  &&
          !g_guiSettings.GetString("scrobbler.librefmpass").IsEmpty()  &&
         g_guiSettings.GetBool("scrobbler.librefmsubmit"));
}

