/*
 * CoinsManager.cpp
 *
 *  Created on: Nov 7, 2012
 *      Author: laureon
 */

#include "CoinsManager.h"

#include "PlayListPlayer.h"
#include "playlists/PlayList.h"
#include "guilib/GUIWindowManager.h"
#include "guilib/LocalizeStrings.h"

CoinsManager::CoinsManager() {
  // TODO Auto-generated constructor stub
  m_dialog = NULL;
  m_coins = -1;
  m_iErasesAvaiable = 0;
}

CoinsManager::~CoinsManager() {
  // TODO Auto-generated destructor stub
}

int64_t CoinsManager::InsertCoin(int64_t Amount) {
  if (!m_dbProfessional.AddCoin(Amount))
    return -1;

  m_coins += Amount;
  m_iErasesAvaiable += Amount;
  return m_coins;
}

int64_t CoinsManager::RemoveCoin(int64_t Amount) {
  if (m_coins <= 0) {
    m_iErasesAvaiable = 0;
    m_coins = 0;
    return 0;
  }

  if (m_coins < Amount)
    Amount = m_coins;

  if (m_dbProfessional.RemoveCoin(Amount)) {
    m_coins -= Amount;
  }

  return m_coins;
}

inline int64_t CoinsManager::GetCoins() {
  return m_coins;
}

int64_t CoinsManager::EraseSong(int64_t Amount) {
  if (m_iErasesAvaiable <=0)
    return 0;

  int iCurrentPlaylist = g_playlistPlayer.GetCurrentPlaylist();
  int iCurrentPlaylistSize = g_playlistPlayer.GetPlaylist(iCurrentPlaylist).size();
  if (iCurrentPlaylistSize <= 0) return 0;

  if (m_iErasesAvaiable < Amount)
    Amount = m_iErasesAvaiable;

  int iRemoved =0;

  if (iCurrentPlaylistSize >= Amount) {
    for (int c = Amount; c > 0; c--) {
      if (InsertCoin() != -1) {
        g_playlistPlayer.Remove(iCurrentPlaylist, g_playlistPlayer.GetPlaylist(iCurrentPlaylist).size()-1);
        m_iErasesAvaiable--;
        iRemoved++;
      }
    }
  }

  return iRemoved;
}

void CoinsManager::RemoveLastSong() {
  int iCurrentPlaylist = g_playlistPlayer.GetCurrentPlaylist();
  if (g_playlistPlayer.GetPlaylist(iCurrentPlaylist).size() > 1) {
    if (InsertCoin() != -1) {
      g_playlistPlayer.Remove(iCurrentPlaylist, g_playlistPlayer.GetPlaylist(iCurrentPlaylist).size()-1);
    }
  }
}


inline bool CoinsManager::HasCoins() {
  return (m_coins > 0);
}

bool CoinsManager::CanQueue() {
  return HasCoins();
}

void CoinsManager::RegisterQueue() {
  RemoveCoin();
}

void CoinsManager::ShowMessage() {
  if (!m_dialog->IsDialogRunning())
    m_dialog->QueueNotification(CGUIDialogKaiToast::Warning, g_localizeStrings.Get(20052),g_localizeStrings.Get(70000),2500);
}

bool CoinsManager::Init() {
  if (!m_dbProfessional.Open()) return false;

  m_coins =  m_dbProfessional.GetCoins();
  m_iErasesAvaiable = m_coins;

  m_dialog = (CGUIDialogKaiToast *)g_windowManager.GetWindow(WINDOW_DIALOG_KAI_TOAST);
  if (!m_dialog) return false;

  return true;
}

CStdString CoinsManager::GetModeInfo() {
  CStdString strLabel;
  strLabel.Format("%02d " +g_localizeStrings.Get(60002), GetCoins());
  return strLabel;
}
