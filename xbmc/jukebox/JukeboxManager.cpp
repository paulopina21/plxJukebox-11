#include "JukeboxManager.h"
#include "PlayListPlayer.h"
#include "playlists/PlayList.h"
#include "settings/GUISettings.h"

CJukeboxManager::CJukeboxManager() {
	m_started = false;
//	CoolDownReset();
}

// STATS AND REPORTS SYSTEM
//bool CJukeboxManager::ExportReport(eREPORT eReportType, const CStdString& strPath, bool bRecoverLast) {
//  return m_ReportsManager.ExportReport(eReportType, strPath, bRecoverLast);
//}



bool CJukeboxManager::Start() {
  m_started =
      m_coinsManager.Init() &&
      m_partyModeManager.Init();

  if (g_guiSettings.GetBool("jukeboxer.autorandom")) {
    m_randomManager.SetActionTime(g_guiSettings.GetInt("jukeboxer.autorandomtime"));
    m_randomManager.Start();
  }

	return m_started;
}

CJukeboxManager::~CJukeboxManager() {
	m_db.Close();
	m_randomManager.Stop();
}

//void CJukeboxManager::CoolDownReset() {
//	m_coolDownCounter = 0;
//	m_coolDownTimer.Reset();
//	m_coolDownTimer.Stop();
//}

//bool CJukeboxManager::InCoolDown() {
//	float seconds = m_coolDownTimer.GetElapsedSeconds();
//	return (seconds <= COOLDOWNTIME) && (seconds != 0.0f) && (m_coolDownTimer.IsRunning());
//}

//void CJukeboxManager::AddCoolDownCount() {
//	m_coolDownCounter += 1;
//	if (m_coolDownCounter == COOLDOWNMAXSONGS) {
//		CoolDownReset();
//		m_coolDownTimer.Start();
//	}
//}

//CStdString CJukeboxManager::GetCoolDownTime() {
//	CStdString strTimer;
//
//	int min = 0;
//	int sec = 0;
//	float waitTime = 0;
//
//	if (InCoolDown()) {
//		waitTime = COOLDOWNTIME - m_coolDownTimer.GetElapsedSeconds();
//		min = waitTime / 60;
//		sec = int(waitTime) % 60;
//	}
//
//	strTimer.Format("%02d:%02d", min,sec);
//
//	return strTimer;
//}

CoinsManager& CJukeboxManager::GetCoinsManager() {
  return m_coinsManager;
}

IModeManager& CJukeboxManager::GetModeManager() {
  switch (g_guiSettings.GetInt("operation.mode"))
  {
    case JUKEBOX_OPMODE_DEFAULT:
    {
      return m_coinsManager;
    }
    break;
    case JUKEBOX_OPMODE_PARTY:
    {
      return m_partyModeManager;
    }
    break;
  }
  return m_coinsManager;
}

RandomManager& CJukeboxManager::GetRandomManager() {
  return m_randomManager;
}

CReportManager& CJukeboxManager::GetReportsManager() {
  return m_ReportsManager;
}

//bool CJukeboxManager::LogPlayedItem(CFileItem* pItem) {
//  return m_ReportsManager.LogPlayedItem(pItem);
//}


//CJukeboxManager& g_jukeboxManager = g_SystemGlobals.m_jukeboxManager;
