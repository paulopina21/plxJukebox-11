
#include "AddonStatusHandler.h"
#include "AddonManager.h"
#include "threads/SingleLock.h"
#include "Application.h"
#include "guilib/GUIWindowManager.h"
#include "GUIDialogAddonSettings.h"
#include "dialogs/GUIDialogYesNo.h"
#include "dialogs/GUIDialogOK.h"
#include "utils/log.h"

namespace ADDON
{

/**********************************************************
 * CAddonStatusHandler - AddOn Status Report Class
 *
 * Used to informate the user about occurred errors and
 * changes inside Add-on's, and ask him what to do.
 *
 */

CCriticalSection CAddonStatusHandler::m_critSection;

CAddonStatusHandler::CAddonStatusHandler(const CStdString &addonID, ADDON_STATUS status, CStdString message, bool sameThread)
  : CThread("CAddonStatusHandler:" + addonID)
{
  if (!CAddonMgr::Get().GetAddon(addonID, m_addon))
    return;

  CLog::Log(LOGINFO, "Called Add-on status handler for '%u' of clientName:%s, clientID:%s (same Thread=%s)", status, m_addon->Name().c_str(), m_addon->ID().c_str(), sameThread ? "yes" : "no");

  m_status  = status;
  m_message = message;

  if (sameThread)
  {
    Process();
  }
  else
  {
    Create(true, THREAD_MINSTACKSIZE);
    SetPriority(-15);
  }
}

CAddonStatusHandler::~CAddonStatusHandler()
{
  StopThread();
}

void CAddonStatusHandler::OnStartup()
{
}

void CAddonStatusHandler::OnExit()
{
}

void CAddonStatusHandler::Process()
{
  CSingleLock lock(m_critSection);

  CStdString heading;
  heading.Format("%s: %s", TranslateType(m_addon->Type(), true).c_str(), m_addon->Name().c_str());

  /* AddOn lost connection to his backend (for ones that use Network) */
  if (m_status == ADDON_STATUS_LOST_CONNECTION)
  {
    CGUIDialogYesNo* pDialog = (CGUIDialogYesNo*)g_windowManager.GetWindow(WINDOW_DIALOG_YES_NO);
    if (!pDialog) return;

    pDialog->SetHeading(heading);
    pDialog->SetLine(1, 24070);
    pDialog->SetLine(2, 24073);

    //send message and wait for user input
    ThreadMessage tMsg = {TMSG_DIALOG_DOMODAL, WINDOW_DIALOG_YES_NO, g_windowManager.GetActiveWindow()};
    g_application.getApplicationMessenger().SendMessage(tMsg, true);

    if (pDialog->IsConfirmed())
      CAddonMgr::Get().GetCallbackForType(m_addon->Type())->RequestRestart(m_addon, false);
  }
  /* Request to restart the AddOn and data structures need updated */
  else if (m_status == ADDON_STATUS_NEED_RESTART)
  {
    CGUIDialogOK* pDialog = (CGUIDialogOK*)g_windowManager.GetWindow(WINDOW_DIALOG_OK);
    if (!pDialog) return;

    pDialog->SetHeading(heading);
    pDialog->SetLine(1, 24074);

    //send message and wait for user input
    ThreadMessage tMsg = {TMSG_DIALOG_DOMODAL, WINDOW_DIALOG_OK, g_windowManager.GetActiveWindow()};
    g_application.getApplicationMessenger().SendMessage(tMsg, true);

    CAddonMgr::Get().GetCallbackForType(m_addon->Type())->RequestRestart(m_addon, true);
  }
  /* Some required settings are missing/invalid */
  else if ((m_status == ADDON_STATUS_NEED_SETTINGS) || (m_status == ADDON_STATUS_NEED_SAVEDSETTINGS))
  {
    CGUIDialogYesNo* pDialogYesNo = (CGUIDialogYesNo*)g_windowManager.GetWindow(WINDOW_DIALOG_YES_NO);
    if (!pDialogYesNo) return;

    pDialogYesNo->SetHeading(heading);
    pDialogYesNo->SetLine(1, 24070);
    pDialogYesNo->SetLine(2, 24072);
    pDialogYesNo->SetLine(3, m_message);

    //send message and wait for user input
    ThreadMessage tMsg = {TMSG_DIALOG_DOMODAL, WINDOW_DIALOG_YES_NO, g_windowManager.GetActiveWindow()};
    g_application.getApplicationMessenger().SendMessage(tMsg, true);

    if (!pDialogYesNo->IsConfirmed()) return;

    if (!m_addon->HasSettings())
      return;

    if (CGUIDialogAddonSettings::ShowAndGetInput(m_addon))
    {
      //todo doesn't dialogaddonsettings save these automatically? should do
      m_addon->SaveSettings();
      CAddonMgr::Get().GetCallbackForType(m_addon->Type())->RequestRestart(m_addon, true);
    }
  }
  /* A unknown event has occurred */
  else if (m_status == ADDON_STATUS_UNKNOWN)
  {
    //CAddonMgr::Get().DisableAddon(m_addon->ID());
    CGUIDialogOK* pDialog = (CGUIDialogOK*)g_windowManager.GetWindow(WINDOW_DIALOG_OK);
    if (!pDialog) return;

    pDialog->SetHeading(heading);
    pDialog->SetLine(1, 24070);
    pDialog->SetLine(2, 24071);
    pDialog->SetLine(3, m_message);

    //send message and wait for user input
    ThreadMessage tMsg = {TMSG_DIALOG_DOMODAL, WINDOW_DIALOG_OK, g_windowManager.GetActiveWindow()};
    g_application.getApplicationMessenger().SendMessage(tMsg, true);
  }
}


} /*namespace ADDON*/

