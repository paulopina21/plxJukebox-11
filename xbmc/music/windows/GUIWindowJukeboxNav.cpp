

#include "GUIWindowJukeboxNav.h"
#include "utils/FileUtils.h"
#include "utils/URIUtils.h"
#include "PlayListPlayer.h"
#include "GUIPassword.h"
#include "dialogs/GUIDialogFileBrowser.h"
#include "settings/GUIDialogContentSettings.h"
#include "filesystem/MusicDatabaseDirectory.h"
#include "filesystem/VideoDatabaseDirectory.h"
#include "PartyModeManager.h"
#include "playlists/PlayList.h"
#include "playlists/PlayListFactory.h"
#include "music/dialogs/GUIDialogMusicScan.h"
#include "video/VideoDatabase.h"
#include "video/windows/GUIWindowVideoNav.h"
#include "music/tags/MusicInfoTag.h"
#include "guilib/GUIWindowManager.h"
#include "dialogs/GUIDialogOK.h"
#include "dialogs/GUIDialogKeyboard.h"
#include "guilib/GUIEditControl.h"
#include "GUIUserMessages.h"
#include "filesystem/File.h"
#include "FileItem.h"
#include "Application.h"
#include "settings/Settings.h"
#include "settings/AdvancedSettings.h"
#include "guilib/LocalizeStrings.h"
#include "utils/log.h"
#include "TextureCache.h"
#include "../../guilib/GUIListContainer.h" // Laureon: Added: Jukebox Music library behavior

using namespace std;
using namespace XFILE;
using namespace PLAYLIST;
using namespace MUSICDATABASEDIRECTORY;

#define CONTROL_BTNVIEWASICONS     2
#define CONTROL_BTNSORTBY          3
#define CONTROL_BTNSORTASC         4
#define CONTROL_BTNTYPE            5
#define CONTROL_LABELFILES        12

#define CONTROL_SEARCH             8
#define CONTROL_FILTER            15
#define CONTROL_BTNPARTYMODE      16
#define CONTROL_BTNMANUALINFO     17
#define CONTROL_BTN_FILTER        19
#define CONTROL_LABELEMPTY        18
#define CONTROL_JUKEBOXLIST				666


CGUIWindowJukeboxNav::CGUIWindowJukeboxNav(void)
  : CGUIWindowJukeboxBase(WINDOW_MUSIC_NAV, "JukeboxNav.xml")
{
  m_vecItems->SetPath("?");
  m_bDisplayEmptyDatabaseMessage = false;
  m_thumbLoader.SetObserver(this);
  m_searchWithEdit = false;
}

CGUIWindowJukeboxNav::~CGUIWindowJukeboxNav(void)
{
}

bool CGUIWindowJukeboxNav::OnMessage(CGUIMessage& message) {

  switch (message.GetMessage()) {
    case GUI_MSG_WINDOW_RESET:
      m_vecItems->SetPath("?");
    break;

//    case GUI_MSG_VISIBLE:
//      if (message.GetSenderId() == CONTROL_JUKEBOXLIST) {
//        UpdateSongsControl();
//      }
//    break;

    case GUI_MSG_WINDOW_DEINIT:
      if (m_thumbLoader.IsLoading())
        m_thumbLoader.StopThread();
      g_advancedSettings.m_fullScreenOnMovieStart = true; // Laureon: Added: Jukebox Music library behavior
    break;

    case GUI_MSG_WINDOW_INIT: {
      /* We don't want to show Autosourced items (ie removable pendrives, memorycards) in Library mode */
      m_rootDir.AllowNonLocalSources(false);

      // is this the first time the window is opened?
      if (m_vecItems->GetPath() == "?" && message.GetStringParam().IsEmpty())
        message.SetStringParam(g_settings.m_defaultMusicLibSource);

      // Laureon: Added: Start on LIBRARY ALBUM LISTING MODE
      message.SetStringParam("musicdb://3/");

      // Laureon: Added: Jukebox mode for music videos in music library
      g_advancedSettings.m_fullScreenOnMovieStart = false; 

      DisplayEmptyDatabaseMessage(false); // reset message state

      if (!CGUIWindowJukeboxBase::OnMessage(message))
        return false;

      //  base class has opened the database, do our check
      DisplayEmptyDatabaseMessage(m_musicdatabase.GetSongsCount() <= 0);

      if (m_bDisplayEmptyDatabaseMessage) {
        // no library - make sure we focus on a known control, and default to the root.
        SET_CONTROL_FOCUS(CONTROL_BTNTYPE, 0);
        m_vecItems->SetPath("");
        SetHistoryForPath("");
        Update("");
      }

      // Laureon: Added: Jukebox Music library behavior
      UpdateSongsControl();
      LoadPlayList("special://masterprofile/playlist.m3u");
      return true;
    }
    break;

    case GUI_MSG_CLICKED: {
      int iControl = message.GetSenderId();
//      if (iControl == CONTROL_BTNPARTYMODE) {
//        if (g_partyModeManager.IsEnabled())
//          g_partyModeManager.Disable();
//        else 
//        {
//          if (!g_partyModeManager.Enable()) {
//            SET_CONTROL_SELECTED(GetID(),CONTROL_BTNPARTYMODE,false);
//            return false;
//          }
//
//          // Playlist directory is the root of the playlist window
//          if (m_guiState.get()) m_guiState->SetPlaylistDirectory("playlistmusic://");
//
//          return true;
//        }
//        UpdateButtons();
//      }
//      else if (iControl == CONTROL_BTNMANUALINFO) {
//        OnManualAlbumInfo();
//        return true;
//      }
//      else 
      if (iControl == CONTROL_SEARCH) {
        if (m_searchWithEdit) {
          // search updated - reset timer
          m_searchTimer.StartZero();
          // grab our search string
          CGUIMessage selected(GUI_MSG_ITEM_SELECTED, GetID(), CONTROL_SEARCH);
          OnMessage(selected);
          SetProperty("search", selected.GetLabel());
          return true;
        }
        CStdString search(GetProperty("search").asString());
        CGUIDialogKeyboard::ShowAndGetFilter(search, true);
        SetProperty("search", search);
        return true;
      }
    }
    break;
    case GUI_MSG_PLAYBACK_STARTED:
      SET_CONTROL_SELECTED(GetID(),CONTROL_BTNPARTYMODE, g_partyModeManager.IsEnabled());
    break;

    case GUI_MSG_NOTIFY_ALL: {
      if (message.GetParam1() == GUI_MSG_SEARCH_UPDATE && IsActive()) {
        // search updated - reset timer
        m_searchTimer.StartZero();
        SetProperty("search", message.GetStringParam());
      }
    }

  }
  return CGUIWindowJukeboxBase::OnMessage(message);
}

bool CGUIWindowJukeboxNav::GetSongsFromAlbum(CFileItemPtr pItem, CFileItemList& items) {
  if (!pItem || !pItem->IsAlbum()) return false;
  
  items.Clear();
  
  if (!m_musicdatabase.GetSongsNav("", items,-1,-1, pItem->GetMusicInfoTag()->GetAlbumID()))
    return false;

  //if (m_videodatabase.Open()) {
   // m_videodatabase.GetMusicVideosByAlbum(pItem->GetMusicInfoTag()->GetAlbum(),items);
    //m_videodatabase.GetMusicVideosNav("",items,-1,-1,-1,-1,-1,pItem->GetMusicInfoTag()->GetAlbumID());
    //m_videodatabase.Close();
  //}
  
  items.FillInDefaultIcons();
  
  return true;
}

void CGUIWindowJukeboxNav::UpdateSongsControl() {
  if (GetControl(CONTROL_JUKEBOXLIST)->IsVisible()) {
    GetSongsFromAlbum(m_vecItems->Get(m_viewControl.GetSelectedItem()), *m_vecTracks);

    CGUIMessage msg(GUI_MSG_LABEL_BIND, GetID(), CONTROL_JUKEBOXLIST, 0, 0, m_vecTracks);
    OnMessage(msg);
  }
}

bool CGUIWindowJukeboxNav::OnAction(const CAction& action)
{
  int actionID = action.GetID();
  bool result = false;
  
  if (actionID == ACTION_STOP) {
    g_playlistPlayer.ClearPlaylist(PLAYLIST_MUSIC);
  }

  if (actionID == ACTION_SCAN_ITEM) {
    int item = m_viewControl.GetSelectedItem();
    CMusicDatabaseDirectory dir;
    if (item > -1 && m_vecItems->Get(item)->m_bIsFolder && (dir.HasAlbumInfo(m_vecItems->Get(item)->GetPath()) || dir.IsArtistDir(m_vecItems->Get(item)->GetPath())))
      OnContextButton(m_vecItems->Get(item),CONTEXT_BUTTON_INFO);

    return true;
  }

  if (actionID == ACTION_MOVE_DOWN || actionID == ACTION_MOVE_UP)
  {
    if (GetFocusedControlID() != CONTROL_JUKEBOXLIST)
      SET_CONTROL_FOCUS(CONTROL_JUKEBOXLIST,0);
  }
  
  if (actionID == ACTION_MOVE_RIGHT || actionID == ACTION_MOVE_LEFT) 
  {
    if (GetFocusedControlID() == CONTROL_JUKEBOXLIST) 
      SET_CONTROL_FOCUS(m_viewControl.GetCurrentControl(),0);

    result = CGUIWindowJukeboxBase::OnAction(action);
    
    UpdateSongsControl();
  }

  if (actionID == ACTION_SELECT_ITEM) 
  {
    if (!GetControl(CONTROL_JUKEBOXLIST)->IsVisible()) return false;
    if (GetFocusedControlID() != CONTROL_JUKEBOXLIST)
      SET_CONTROL_FOCUS(CONTROL_JUKEBOXLIST,0);
  }

  if (!result) 
    result = CGUIWindowJukeboxBase::OnAction(action);

  return result;
}

CStdString CGUIWindowJukeboxNav::GetQuickpathName(const CStdString& strPath) const
{
  if (strPath.Equals("musicdb://1/"))
    return "Genres";
  else if (strPath.Equals("musicdb://2/"))
    return "Artists";
  else if (strPath.Equals("musicdb://3/"))
    return "Albums";
  else if (strPath.Equals("musicdb://4/"))
    return "Songs";
  else if (strPath.Equals("musicdb://5/"))
    return "Top100";
  else if (strPath.Equals("musicdb://5/2/"))
    return "Top100Songs";
  else if (strPath.Equals("musicdb://5/1/"))
    return "Top100Albums";
  else if (strPath.Equals("musicdb://6/"))
    return "RecentlyAddedAlbums";
  else if (strPath.Equals("musicdb://7/"))
    return "RecentlyPlayedAlbums";
  else if (strPath.Equals("musicdb://8/"))
    return "Compilations";
  else if (strPath.Equals("musicdb://9/"))
    return "Years";
  else if (strPath.Equals("musicdb://10/"))
    return "Singles";
  else if (strPath.Equals("special://musicplaylists/"))
    return "Playlists";
  else
  {
    CLog::Log(LOGERROR, "  CGUIWindowJukeboxNav::GetQuickpathName: Unknown parameter (%s)", strPath.c_str());
    return strPath;
  }
}

bool CGUIWindowJukeboxNav::OnClick(CFileItemPtr pItem)
{
  if (pItem->GetPath().Left(14) == "musicsearch://")
  {
    if (m_searchWithEdit)
      OnSearchUpdate();
    else
    {
      CStdString search(GetProperty("search").asString());
      CGUIDialogKeyboard::ShowAndGetFilter(search, true);
      SetProperty("search", search);
    }
    return true;
  }
  if (pItem->IsMusicDb() && !pItem->m_bIsFolder)
    m_musicdatabase.SetPropertiesForFileItem(*pItem);

  return CGUIWindowJukeboxBase::OnClick(pItem);
}

bool CGUIWindowJukeboxNav::GetDirectory(const CStdString &strDirectory, CFileItemList &items)
{
  if (m_bDisplayEmptyDatabaseMessage)
    return true;

  if (strDirectory.IsEmpty())
    AddSearchFolder();

  if (m_thumbLoader.IsLoading())
    m_thumbLoader.StopThread();

  bool bResult = CGUIWindowJukeboxBase::GetDirectory(strDirectory, items);
  if (bResult)
  {
    if (items.IsPlayList())
      OnRetrieveMusicInfo(items);
    if (!items.IsMusicDb())
    {
      items.SetCachedMusicThumbs();
      m_thumbLoader.Load(*m_vecItems);
    }
  }

  // update our content in the info manager
  if (strDirectory.Left(10).Equals("videodb://"))
  {
    CVideoDatabaseDirectory dir;
    VIDEODATABASEDIRECTORY::NODE_TYPE node = dir.GetDirectoryChildType(strDirectory);
    if (node == VIDEODATABASEDIRECTORY::NODE_TYPE_TITLE_MUSICVIDEOS)
      items.SetContent("musicvideos");
  }
  else if (strDirectory.Left(10).Equals("musicdb://"))
  {
    CMusicDatabaseDirectory dir;
    NODE_TYPE node = dir.GetDirectoryChildType(strDirectory);
    if (node == NODE_TYPE_ALBUM ||
      node == NODE_TYPE_ALBUM_RECENTLY_ADDED ||
      node == NODE_TYPE_ALBUM_RECENTLY_PLAYED ||
      node == NODE_TYPE_ALBUM_TOP100 ||
      node == NODE_TYPE_ALBUM_COMPILATIONS ||
      node == NODE_TYPE_YEAR_ALBUM)
      items.SetContent("albums");
    else if (node == NODE_TYPE_ARTIST)
      items.SetContent("artists");
    else if (node == NODE_TYPE_SONG ||
      node == NODE_TYPE_SONG_TOP100 ||
      node == NODE_TYPE_SINGLES)
      items.SetContent("songs");
    else if (node == NODE_TYPE_GENRE)
      items.SetContent("genres");
    else if (node == NODE_TYPE_YEAR)
      items.SetContent("years");
  }
  else if (strDirectory.Equals("special://musicplaylists"))
    items.SetContent("playlists");
  else if (strDirectory.Equals("plugin://music/"))
    items.SetContent("plugins");
  else if (items.IsPlayList())
    items.SetContent("songs");

  return bResult;
}

void CGUIWindowJukeboxNav::UpdateButtons()
{
  CGUIWindowJukeboxBase::UpdateButtons();

  // Update object count
  int iItems = m_vecItems->Size();
  if (iItems)
  {
    // check for parent dir and "all" items
    // should always be the first two items
    for (int i = 0; i <= (iItems>=2 ? 1 : 0); i++)
    {
      CFileItemPtr pItem = m_vecItems->Get(i);
      if (pItem->IsParentFolder()) iItems--;
      if (pItem->GetPath().Left(4).Equals("/-1/")) iItems--;
    }
    // or the last item
    if (m_vecItems->Size() > 2 &&
      m_vecItems->Get(m_vecItems->Size()-1)->GetPath().Left(4).Equals("/-1/"))
      iItems--;
  }
  CStdString items;
  items.Format("%i %s", iItems, g_localizeStrings.Get(127).c_str());
  SET_CONTROL_LABEL(CONTROL_LABELFILES, items);

  // set the filter label
  CStdString strLabel;

  // "Playlists"
  if (m_vecItems->GetPath().Equals("special://musicplaylists/"))
    strLabel = g_localizeStrings.Get(136);
  // "{Playlist Name}"
  else if (m_vecItems->IsPlayList())
  {
    // get playlist name from path
    CStdString strDummy;
    URIUtils::Split(m_vecItems->GetPath(), strDummy, strLabel);
  }
  // everything else is from a musicdb:// path
  else
  {
    CMusicDatabaseDirectory dir;
    dir.GetLabel(m_vecItems->GetPath(), strLabel);
  }

  SET_CONTROL_LABEL(CONTROL_FILTER, strLabel);

  SET_CONTROL_SELECTED(GetID(),CONTROL_BTNPARTYMODE, g_partyModeManager.IsEnabled());
}

void CGUIWindowJukeboxNav::PlayItem(CFileItemPtr pItem)
{
  // unlike additemtoplaylist, we need to check the items here
  // before calling it since the current playlist will be stopped
  // and cleared!

  // root is not allowed
  if (m_vecItems->IsVirtualDirectoryRoot())
    return;

  CGUIWindowJukeboxBase::PlayItem(pItem);
}

void CGUIWindowJukeboxNav::OnWindowLoaded()
{
  const CGUIControl *control = GetControl(CONTROL_SEARCH);
  m_searchWithEdit = (control && control->GetControlType() == CGUIControl::GUICONTROL_EDIT);

  CGUIWindowJukeboxBase::OnWindowLoaded();

  if (m_searchWithEdit)
  {
    SendMessage(GUI_MSG_SET_TYPE, CONTROL_SEARCH, CGUIEditControl::INPUT_TYPE_SEARCH);
    SET_CONTROL_LABEL2(CONTROL_SEARCH, GetProperty("search").asString());
  }
}

void CGUIWindowJukeboxNav::GetContextButtons(CFileItemPtr pItem, CContextButtons &buttons)
{
  CGUIWindowJukeboxBase::GetContextButtons(pItem, buttons);

  CGUIDialogMusicScan *musicScan = (CGUIDialogMusicScan *)g_windowManager.GetWindow(WINDOW_DIALOG_MUSIC_SCAN);
  if (pItem && (pItem->GetExtraInfo().Find("lastfm") < 0))
  {
//    // are we in the playlists location?
    bool inPlaylists = m_vecItems->GetPath().Equals(CUtil::MusicPlaylistsLocation()) ||
      m_vecItems->GetPath().Equals("special://musicplaylists/");

    CMusicDatabaseDirectory dir;
    // enable music info button on an album or on a song.
//    if (pItem->IsAudio() && !pItem->IsPlayList() && !pItem->IsSmartPlayList() &&
//      !pItem->IsLastFM() && !pItem->m_bIsFolder)
//    {
//      buttons.Add(CONTEXT_BUTTON_SONG_INFO, 658);
//    }
//    else if (pItem->IsVideoDb())
//    {
//      if (!pItem->m_bIsFolder) // music video
//        buttons.Add(CONTEXT_BUTTON_INFO, 20393);
//      if (pItem->GetPath().Left(14).Equals("videodb://3/4/") &&
//        pItem->GetPath().size() > 14 && pItem->m_bIsFolder)
//      {
//        long idArtist = m_musicdatabase.GetArtistByName(pItem->GetLabel());
//        if (idArtist > - 1)
//          buttons.Add(CONTEXT_BUTTON_INFO,21891);
//      }
//    }
//    else if (!inPlaylists && (dir.HasAlbumInfo(pItem->GetPath())||
//      dir.IsArtistDir(pItem->GetPath())   )      &&
//      !dir.IsAllItem(pItem->GetPath()) && !pItem->IsParentFolder() &&
//      !pItem->IsLastFM() && !pItem->IsPlugin() && !pItem->IsScript() &&
//      !pItem->GetPath().Left(14).Equals("musicsearch://"))
//    {
//      if (dir.IsArtistDir(pItem->GetPath()))
//        buttons.Add(CONTEXT_BUTTON_INFO, 21891);
//      else
        buttons.Add(CONTEXT_BUTTON_INFO, 13351);
//    }

    // enable query all albums button only in album view
//    if (dir.HasAlbumInfo(pItem->GetPath()) && !dir.IsAllItem(pItem->GetPath()) &&
//      pItem->m_bIsFolder && !pItem->IsVideoDb() && !pItem->IsParentFolder()   &&
//      !pItem->IsLastFM()                                                     &&
//      !pItem->IsPlugin() && !pItem->GetPath().Left(14).Equals("musicsearch://"))
//    {
//      buttons.Add(CONTEXT_BUTTON_INFO_ALL, 20059);
//    }

    // enable query all artist button only in album view
//    if (dir.IsArtistDir(pItem->GetPath()) && !dir.IsAllItem(pItem->GetPath()) &&
//      pItem->m_bIsFolder && !pItem->IsVideoDb())
//    {
//      ADDON::ScraperPtr info;
//      m_musicdatabase.GetScraperForPath(pItem->GetPath(), info, ADDON::ADDON_SCRAPER_ARTISTS);
//      if (info && info->Supports(CONTENT_ARTISTS))
//        buttons.Add(CONTEXT_BUTTON_INFO_ALL, 21884);
//    }

    //Set default or clear default
    NODE_TYPE nodetype = dir.GetDirectoryType(pItem->GetPath());
    if (!pItem->IsParentFolder() && !inPlaylists &&
      (nodetype == NODE_TYPE_ROOT ||  nodetype == NODE_TYPE_OVERVIEW || nodetype == NODE_TYPE_TOP100))
    {
      if (!pItem->GetPath().Equals(g_settings.m_defaultMusicLibSource))
        buttons.Add(CONTEXT_BUTTON_SET_DEFAULT, 13335); // set default
      if (strcmp(g_settings.m_defaultMusicLibSource, ""))
        buttons.Add(CONTEXT_BUTTON_CLEAR_DEFAULT, 13403); // clear default
    }
//    NODE_TYPE childtype = dir.GetDirectoryChildType(pItem->GetPath());
//    if (childtype == NODE_TYPE_ALBUM               ||
//      childtype == NODE_TYPE_ARTIST              ||
//      nodetype == NODE_TYPE_GENRE                ||
//      nodetype == NODE_TYPE_ALBUM                ||
//      nodetype == NODE_TYPE_ALBUM_RECENTLY_ADDED ||
//      nodetype == NODE_TYPE_ALBUM_COMPILATIONS)
//    {
//      // we allow the user to set content for
//      // 1. general artist and album nodes
//      // 2. specific per genre
//      // 3. specific per artist
//      // 4. specific per album
//      buttons.Add(CONTEXT_BUTTON_SET_CONTENT,20195);
//    }
//    if (pItem->HasMusicInfoTag() && pItem->GetMusicInfoTag()->GetArtist().size() > 0)
//    {
//      CVideoDatabase database;
//      database.Open();
//      if (database.GetMatchingMusicVideo(pItem->GetMusicInfoTag()->GetArtist()) > -1)
//        buttons.Add(CONTEXT_BUTTON_GO_TO_ARTIST, 20400);
//    }
//    if (pItem->HasMusicInfoTag() && pItem->GetMusicInfoTag()->GetArtist().size() > 0 &&
//      pItem->GetMusicInfoTag()->GetAlbum().size() > 0 &&
//      pItem->GetMusicInfoTag()->GetTitle().size() > 0)
//    {
//      CVideoDatabase database;
//      database.Open();
//      if (database.GetMatchingMusicVideo(pItem->GetMusicInfoTag()->GetArtist(),pItem->GetMusicInfoTag()->GetAlbum(),pItem->GetMusicInfoTag()->GetTitle()) > -1)
//        buttons.Add(CONTEXT_BUTTON_PLAY_OTHER, 20401);
//    }
//    if (pItem->HasVideoInfoTag() && !pItem->m_bIsFolder)
//    {
//      if (pItem->GetVideoInfoTag()->m_playCount > 0)
//        buttons.Add(CONTEXT_BUTTON_MARK_UNWATCHED, 16104); //Mark as UnWatched
//      else
//        buttons.Add(CONTEXT_BUTTON_MARK_WATCHED, 16103);   //Mark as Watched
//      if ((g_settings.GetCurrentProfile().canWriteDatabases() || g_passwordManager.bMasterUser) && !pItem->IsPlugin())
//      {
//        buttons.Add(CONTEXT_BUTTON_RENAME, 16105);
//        buttons.Add(CONTEXT_BUTTON_DELETE, 646);
//      }
//    }
//    if (inPlaylists && !URIUtils::GetFileName(pItem->GetPath()).Equals("PartyMode.xsp")
//      && (pItem->IsPlayList() || pItem->IsSmartPlayList()))
//      buttons.Add(CONTEXT_BUTTON_DELETE, 117);
//
//    if (pItem->IsPlugin() || pItem->IsScript() || m_vecItems->IsPlugin())
//      buttons.Add(CONTEXT_BUTTON_PLUGIN_SETTINGS, 1045);
  }
  // noncontextual buttons

  if (musicScan && musicScan->IsScanning())
    buttons.Add(CONTEXT_BUTTON_STOP_SCANNING, 13353);     // Stop Scanning
  else if (musicScan)
    buttons.Add(CONTEXT_BUTTON_UPDATE_LIBRARY, 653);

  CGUIWindowJukeboxBase::GetNonContextButtons(buttons);
}

bool CGUIWindowJukeboxNav::OnContextButton(CFileItemPtr pItem, CONTEXT_BUTTON button)
{
  switch (button)
  {
  case CONTEXT_BUTTON_INFO:
    {
      if (!pItem->IsVideoDb())
        return CGUIWindowJukeboxBase::OnContextButton(pItem,button);

      //// music videos - artists
      //if (pItem->GetPath().Left(14).Equals("videodb://3/4/"))
      //{
      //  long idArtist = m_musicdatabase.GetArtistByName(pItem->GetLabel());
      //  if (idArtist == -1)
      //    return false;
      //  CStdString path; path.Format("musicdb://2/%ld/", idArtist);
      //  CArtist artist;
      //  m_musicdatabase.GetArtistInfo(idArtist,artist,false);
      //  *pItem = CFileItem(artist);
      //  pItem->SetPath(path);
      //  CGUIWindowJukeboxBase::OnContextButton(itemNumber,button);
      //  Update(m_vecItems->GetPath());
      //  m_viewControl.SetSelectedItem(itemNumber);
      //  return true;
      //}

      // music videos - albums
      if (pItem->GetPath().Left(14).Equals("videodb://3/5/"))
      {
        long idAlbum = m_musicdatabase.GetAlbumByName(pItem->GetLabel());
        if (idAlbum == -1)
          return false;
        CStdString path; path.Format("musicdb://3/%ld/", idAlbum);
        CAlbum album;
        m_musicdatabase.GetAlbumInfo(idAlbum,album,NULL);
        *pItem = CFileItem(path,album);
        pItem->SetPath(path);
        CGUIWindowJukeboxBase::OnContextButton(pItem,button);
        Update(m_vecItems->GetPath());
        //m_viewControl.SetSelectedItem(itemNumber);
        return true;
      }

      if (pItem->HasVideoInfoTag() && !pItem->GetVideoInfoTag()->m_strTitle.IsEmpty())
      {
        CGUIWindowVideoNav* pWindow = (CGUIWindowVideoNav*)g_windowManager.GetWindow(WINDOW_VIDEO_NAV);
        if (pWindow)
        {
          ADDON::ScraperPtr info;
          pWindow->OnInfo(pItem.get(),info);
          Update(m_vecItems->GetPath());
        }
      }
      return true;
    }

  case CONTEXT_BUTTON_INFO_ALL:
    OnInfoAll(pItem);
    return true;

  case CONTEXT_BUTTON_UPDATE_LIBRARY:
    {
      CGUIDialogMusicScan *scanner = (CGUIDialogMusicScan *)g_windowManager.GetWindow(WINDOW_DIALOG_MUSIC_SCAN);
      if (scanner)
        scanner->StartScanning("");
      return true;
    }

  case CONTEXT_BUTTON_SET_DEFAULT:
    g_settings.m_defaultMusicLibSource = GetQuickpathName(pItem->GetPath());
    g_settings.Save();
    return true;

  case CONTEXT_BUTTON_CLEAR_DEFAULT:
    g_settings.m_defaultMusicLibSource.Empty();
    g_settings.Save();
    return true;

//  case CONTEXT_BUTTON_GO_TO_ARTIST:
//    {
//      CStdString strPath;
//      CVideoDatabase database;
//      database.Open();
//      strPath.Format("videodb://3/4/%ld/",database.GetMatchingMusicVideo(pItem->GetMusicInfoTag()->GetArtist()));
//      g_windowManager.ActivateWindow(WINDOW_VIDEO_NAV,strPath);
//      return true;
//    }

  case CONTEXT_BUTTON_PLAY_OTHER:
    {
      CVideoDatabase database;
      database.Open();
      CVideoInfoTag details;
      database.GetMusicVideoInfo("",details,database.GetMatchingMusicVideo(pItem->GetMusicInfoTag()->GetArtist(),pItem->GetMusicInfoTag()->GetAlbum(),pItem->GetMusicInfoTag()->GetTitle()));
      g_application.getApplicationMessenger().PlayFile(CFileItem(details));
      return true;
    }

  case CONTEXT_BUTTON_MARK_WATCHED:
    CGUIWindowVideoBase::MarkWatched(pItem,true);
    CUtil::DeleteVideoDatabaseDirectoryCache();
    Update(m_vecItems->GetPath());
    return true;

  case CONTEXT_BUTTON_MARK_UNWATCHED:
    CGUIWindowVideoBase::MarkWatched(pItem,false);
    CUtil::DeleteVideoDatabaseDirectoryCache();
    Update(m_vecItems->GetPath());
    return true;

  case CONTEXT_BUTTON_RENAME:
    CGUIWindowVideoBase::UpdateVideoTitle(pItem.get());
    CUtil::DeleteVideoDatabaseDirectoryCache();
    Update(m_vecItems->GetPath());
    return true;

  case CONTEXT_BUTTON_DELETE:
    if (pItem->IsPlayList() || pItem->IsSmartPlayList())
    {
      pItem->m_bIsFolder = false;
      CFileUtils::DeleteItem(pItem);
    }
    else
    {
      CGUIWindowVideoNav::DeleteItem(pItem.get());
      CUtil::DeleteVideoDatabaseDirectoryCache();
    }
    Update(m_vecItems->GetPath());
    return true;

  case CONTEXT_BUTTON_SET_CONTENT:
    {
      bool bScan=false;
      ADDON::ScraperPtr scraper;
      CStdString path(pItem->GetPath());
      CQueryParams params;
      CDirectoryNode::GetDatabaseInfo(pItem->GetPath(), params);
      CONTENT_TYPE content = CONTENT_ALBUMS;
      if (params.GetAlbumId() != -1)
        path.Format("musicdb://3/%i/",params.GetAlbumId());
      else if (params.GetArtistId() != -1)
      {
        path.Format("musicdb://2/%i/",params.GetArtistId());
        content = CONTENT_ARTISTS;
      }

      if (m_vecItems->GetPath().Equals("musicdb://1/") || pItem->GetPath().Equals("musicdb://2/"))
      {
        content = CONTENT_ARTISTS;
      }

      if (!m_musicdatabase.GetScraperForPath(path, scraper, ADDON::ScraperTypeFromContent(content)))
      {
        ADDON::AddonPtr defaultScraper;
        if (ADDON::CAddonMgr::Get().GetDefault(ADDON::ScraperTypeFromContent(content), defaultScraper))
        {
          scraper = boost::dynamic_pointer_cast<ADDON::CScraper>(defaultScraper->Clone(defaultScraper));
        }
      }

      if (CGUIDialogContentSettings::Show(scraper, bScan, content))
      {
        m_musicdatabase.SetScraperForPath(path,scraper);
        if (bScan)
          OnInfoAll(pItem,true);
      }
      return true;
    }

  default:
    break;
  }

  return CGUIWindowJukeboxBase::OnContextButton(pItem, button);
}

bool CGUIWindowJukeboxNav::GetSongsFromPlayList(const CStdString& strPlayList, CFileItemList &items)
{
  CStdString strParentPath=m_history.GetParentPath();

  if (m_guiState.get() && !m_guiState->HideParentDirItems())
  {
    CFileItemPtr pItem(new CFileItem(".."));
    pItem->SetPath(strParentPath);
    items.Add(pItem);
  }

  items.SetPath(strPlayList);
  CLog::Log(LOGDEBUG,"CGUIWindowJukeboxNav, opening playlist [%s]", strPlayList.c_str());

  auto_ptr<CPlayList> pPlayList (CPlayListFactory::Create(strPlayList));
  if ( NULL != pPlayList.get())
  {
    // load it
    if (!pPlayList->Load(strPlayList))
    {
      CGUIDialogOK::ShowAndGetInput(6, 0, 477, 0);
      return false; //hmmm unable to load playlist?
    }
    CPlayList playlist = *pPlayList;
    // convert playlist items to songs
    for (int i = 0; i < (int)playlist.size(); ++i)
    {
      items.Add(playlist[i]);
    }
  }

  return true;
}

void CGUIWindowJukeboxNav::DisplayEmptyDatabaseMessage(bool bDisplay)
{
  m_bDisplayEmptyDatabaseMessage = bDisplay;
}

void CGUIWindowJukeboxNav::OnSearchUpdate()
{
  CStdString search(GetProperty("search").asString());
  CURL::Encode(search);
  if (!search.IsEmpty())
  {
    CStdString path = "musicsearch://" + search + "/";
    m_history.ClearPathHistory();
    Update(path);
  }
  else if (m_vecItems->IsVirtualDirectoryRoot())
  {
    Update("");
  }
}

void CGUIWindowJukeboxNav::FrameMove()
{
  static const int search_timeout = 2000;
  // update our searching
  if (m_searchTimer.IsRunning() && m_searchTimer.GetElapsedMilliseconds() > search_timeout)
  {
    m_searchTimer.Stop();
    OnSearchUpdate();
  }
  if (m_bDisplayEmptyDatabaseMessage)
    SET_CONTROL_LABEL(CONTROL_LABELEMPTY,g_localizeStrings.Get(745)+'\n'+g_localizeStrings.Get(746));
  else
    SET_CONTROL_LABEL(CONTROL_LABELEMPTY,"");
  CGUIWindowJukeboxBase::FrameMove();
}

void CGUIWindowJukeboxNav::OnPrepareFileItems(CFileItemList &items)
{
  CGUIWindowJukeboxBase::OnPrepareFileItems(items);
  // set fanart
  SetupFanart(items);
}

void CGUIWindowJukeboxNav::AddSearchFolder()
{
  // we use a general viewstate (and not our member) here as our
  // current viewstate may be specific to some other folder, and
  // we know we're in the root here
  CFileItemList items;
  CGUIViewState* viewState = CGUIViewState::GetViewState(GetID(), items);
  if (viewState)
  {
    // add our remove the musicsearch source
    VECSOURCES &sources = viewState->GetSources();
    bool haveSearchSource = false;
    bool needSearchSource = !GetProperty("search").empty() || !m_searchWithEdit; // we always need it if we don't have the edit control
    for (IVECSOURCES it = sources.begin(); it != sources.end(); ++it)
    {
      CMediaSource& share = *it;
      if (share.strPath == "musicsearch://")
      {
        haveSearchSource = true;
        if (!needSearchSource)
        { // remove it
          sources.erase(it);
          break;
        }
      }
    }
    if (!haveSearchSource && needSearchSource)
    {
      // add earch share
      CMediaSource share;
      share.strName=g_localizeStrings.Get(137); // Search
      share.strPath = "musicsearch://";
      share.m_iDriveType = CMediaSource::SOURCE_TYPE_LOCAL;
      sources.push_back(share);
    }
    m_rootDir.SetSources(sources);
    delete viewState;
  }
}

CStdString CGUIWindowJukeboxNav::GetStartFolder(const CStdString &dir)
{
  if (dir.Equals("Genres"))
    return "musicdb://1/";
  else if (dir.Equals("Artists"))
    return "musicdb://2/";
  else if (dir.Equals("Albums"))
    return "musicdb://3/";
  else if (dir.Equals("Singles"))
    return "musicdb://10/";
  else if (dir.Equals("Songs"))
    return "musicdb://4/";
  else if (dir.Equals("Top100"))
    return "musicdb://5/";
  else if (dir.Equals("Top100Songs"))
    return "musicdb://5/1/";
  else if (dir.Equals("Top100Albums"))
    return "musicdb://5/2/";
  else if (dir.Equals("RecentlyAddedAlbums"))
    return "musicdb://6/";
  else if (dir.Equals("RecentlyPlayedAlbums"))
    return "musicdb://7/";
  else if (dir.Equals("Compilations"))
    return "musicdb://8/";
  else if (dir.Equals("Years"))
    return "musicdb://9/";
  return CGUIWindowJukeboxBase::GetStartFolder(dir);
}
