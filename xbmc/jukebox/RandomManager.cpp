/*
 * RandomManager.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: laureon
 */

#include "RandomManager.h"
#include <time.h>

#include "music/MusicDatabase.h"
#include "music/tags/MusicInfoTag.h"

//#include "settings/GUISettings.h"
#include "utils/log.h"

#include "PlayListPlayer.h"
#include "FileItem.h"
#include "Application.h"

RandomManager::RandomManager() {
  m_StopWatchMaxTime = 0;
  m_history.clear();
  bActive = false;
  Reset();
}

RandomManager::~RandomManager() {
  // TODO Auto-generated destructor stub
}

void RandomManager::Reset() {
  m_StopWatch.Reset();
  CLog::Log(LOGDEBUG, "SmartRandom: Timer reseted");
}

void RandomManager::Stop() {
  bActive = false;
  m_StopWatch.Stop();
  StopThread();
  CLog::Log(LOGNOTICE, "SmartRandom: Deactivated");
}

inline bool RandomManager::ItsTime() {
  float minutes = m_StopWatch.GetElapsedSeconds() / 60;
  return (minutes >= m_StopWatchMaxTime) && (minutes != 0.0f) && (m_StopWatch.IsRunning());
}

void RandomManager::Process() {
  while (bActive)
  {
    if (ItsTime())
    {
      DoWork();
    }
    Sleep(1000);
  }
}

void RandomManager::DoWork() {
  if (!bActive) return;

  if (g_application.IsPlaying() || g_jukeboxManager.GetCoinsManager().CanQueue()) {
    Reset();
    return;
  }

  CMusicDatabase database;
  if (!database.Open()) return;

  CStdString whereClause = GetWhereClauseWithHistory();
  CFileItemPtr item(new CFileItem);
  int songID;
  unsigned int ilasttime = time(0);

  do {
    if ( !ItsTime() ) return;

    if (time(0) != ilasttime)
    {
      ilasttime = time(0);
      srand(ilasttime);
    }

    if (!database.GetRandomSong(item.get(), songID, whereClause)) return;

  } while (!item.get()->Exists());

//  g_playlistPlayer.ClearPlaylist(PLAYLIST_MUSIC);
//  g_playlistPlayer.Reset();
  g_playlistPlayer.Add(PLAYLIST_MUSIC, item);
  g_playlistPlayer.SetCurrentPlaylist(PLAYLIST_MUSIC);
  if (g_playlistPlayer.Play()) {
    AddToHistory(songID);
    Reset();
    CStdString strArtist =  item.get()->GetMusicInfoTag()->GetAlbumArtist();

    if (strArtist.empty())
      strArtist = item.get()->GetMusicInfoTag()->GetArtist();

    CStdString strAlbum =  item.get()->GetMusicInfoTag()->GetAlbum();
    CStdString strTitle = item.get()->GetMusicInfoTag()->GetTitle();

    int iTrack = item.get()->GetMusicInfoTag()->GetTrackNumber();

    CLog::Log( LOGNOTICE, "SmartRandom: Playing: %s - %s/%02d - %s", strArtist.c_str(), strAlbum.c_str(), iTrack, strTitle.c_str() );
  }
}

void RandomManager::SetActionTime(int iTime) {
  m_StopWatchMaxTime = iTime;
}

//void RandomManager::UpdateConfig() {
//  bool bEnabled = g_guiSettings.GetBool("jukeboxer.autorandom");
//  m_StopWatchMaxTime = g_guiSettings.GetInt("jukeboxer.autorandomtime");
//}

void RandomManager::Start() {
  StopThread();
  Create();
  SetPriority( GetMinPriority() );
  m_StopWatch.Start();
  bActive = true;
  CLog::Log(LOGNOTICE, "SmartRandom: Activated");
}

void RandomManager::AddToHistory(int songID)
{
  m_history.push_back(songID);
}

CStdString RandomManager::GetWhereClauseWithHistory() const
{
  CStdString historyWhereMusic;
  // now add this on to the normal where clause
  if (m_history.size())
  {
    historyWhereMusic = "where songview.idSong not in (";

    for (unsigned int i = 0; i < m_history.size(); i++)
    {
      CStdString number;
      number.Format("%i,", m_history[i]);
      historyWhereMusic += number;
    }

    historyWhereMusic.TrimRight(",");
    historyWhereMusic += ")";
  }

  return historyWhereMusic;
}
