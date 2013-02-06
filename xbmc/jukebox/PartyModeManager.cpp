/*
 * PartyModeManager.cpp
 *
 *  Created on: Nov 13, 2012
 *      Author: laureon
 */

#include "PartyModeManager.h"
#include "settings/GUISettings.h"
#include "guilib/GUIWindowManager.h"
#include "guilib/LocalizeStrings.h"
#include "PlayListPlayer.h"
#include "playlists/PlayList.h"

namespace plxJukebox {

PartyModeManager::PartyModeManager() {
  // TODO Auto-generated constructor stub
  m_dialog = NULL;
  m_iCurrentPlaylist = 0;
  m_iPlaylistMaxSize = 0;
  m_iPlaylistSize = 0;
  m_iQueuesAllowed = 0;
  m_iQueueWait = 0;
}

PartyModeManager::~PartyModeManager() {
  // TODO Auto-generated destructor stub
}

void PartyModeManager::UpdateParams() {
  m_iCurrentPlaylist   = g_playlistPlayer.GetCurrentPlaylist();
  m_iPlaylistSize         = g_playlistPlayer.GetPlaylist(m_iCurrentPlaylist).GetPlayable();
  m_iPlaylistMaxSize  = g_guiSettings.GetInt("operation.partymode_maxlistsize");
  m_iQueueWait         = g_guiSettings.GetInt("operation.partymode_queuewait");

  if (m_iPlaylistSize <=  m_iPlaylistMaxSize - m_iQueueWait)
    m_iQueuesAllowed = m_iPlaylistMaxSize - m_iPlaylistSize;

  if (m_iPlaylistSize == -1)
    m_iQueuesAllowed = m_iPlaylistMaxSize;
}

bool PartyModeManager::CanQueue() {
  UpdateParams();
  if (m_iPlaylistMaxSize == 0) return true;

  return m_iQueuesAllowed > 0;
}

void PartyModeManager::RegisterQueue() {
  m_iQueuesAllowed--;
}

void PartyModeManager::ShowMessage() {
  if (!m_dialog->IsDialogRunning())
    m_dialog->QueueNotification(CGUIDialogKaiToast::Warning, g_localizeStrings.Get(20052), g_localizeStrings.Get(70001),2500);
}

bool PartyModeManager::Init() {
  UpdateParams();

  m_dialog = (CGUIDialogKaiToast *)g_windowManager.GetWindow(WINDOW_DIALOG_KAI_TOAST);
  if (!m_dialog) return false;

  return true;
}

CStdString PartyModeManager::GetModeInfo() {
  CStdString strLabel;
  if (m_iQueuesAllowed <= 0)
    strLabel.Format(g_localizeStrings.Get(60003));
  else
    strLabel.Format("%02d " +g_localizeStrings.Get(60002), m_iQueuesAllowed);

  return strLabel;
}

} /* namespace plxJukebox */
