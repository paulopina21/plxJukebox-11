

#include "LastFMDirectory.h"
#include "DirectoryCache.h"
#include "music/tags/MusicInfoTag.h"
#include "URL.h"
#include "guilib/GUIWindowManager.h"
#include "dialogs/GUIDialogProgress.h"
#include "settings/GUISettings.h"
#include "FileItem.h"
#include "FileCurl.h"
#include "utils/StringUtils.h"
#include "guilib/LocalizeStrings.h"
#include "utils/log.h"

using namespace MUSIC_INFO;
using namespace XFILE;

#define AUDIOSCROBBLER_BASE_URL      "http://ws.audioscrobbler.com/1.0/"

CLastFMDirectory::CLastFMDirectory()
{
  m_Error = false;
  m_Downloaded = false;
}

CLastFMDirectory::~CLastFMDirectory()
{
}

CStdString CLastFMDirectory::BuildURLFromInfo()
{
  CStdString strURL = (CStdString)AUDIOSCROBBLER_BASE_URL;
  strURL += m_objtype + "/" + m_encodedobjname + "/" + m_objrequest + ".xml";

  return strURL;
}

bool CLastFMDirectory::RetrieveList(CStdString url)
{
  m_dlgProgress = (CGUIDialogProgress*)g_windowManager.GetWindow(WINDOW_DIALOG_PROGRESS);
  if (m_dlgProgress)
  {
    m_dlgProgress->ShowProgressBar(false);
    m_dlgProgress->SetHeading(2);
    m_dlgProgress->SetLine(0, 15279);
    m_dlgProgress->SetLine(1, m_objrequest);
    m_dlgProgress->SetLine(2, m_objname);
    m_dlgProgress->StartModal();
    m_dlgProgress->Progress();
  }

  CThread thread(this);
  m_strSource = url;
  m_strDestination = "special://temp/lastfm.xml";
  thread.Create();

  while (!m_Downloaded)
  {
    m_dlgProgress->Progress();

    if (m_dlgProgress->IsCanceled())
    {
      m_http.Cancel();
      thread.StopThread();
      m_dlgProgress->Close();
      return false;
    }
  }

  if (!m_dlgProgress->IsCanceled() && m_Error)
  {
    if (m_dlgProgress) m_dlgProgress->Close();
    SetErrorDialog(257, 15280, 0, 0);
    CLog::Log(LOGERROR, "Unable to retrieve list from last.fm");
    return false;
  }


  if (!m_xmlDoc.LoadFile(m_strDestination))
  {
    if (m_dlgProgress) m_dlgProgress->Close();
    SetErrorDialog(257, 15280, 0, 0);
    CLog::Log(LOGERROR, "Error parsing file from audioscrobbler web services, Line %d\n%s", m_xmlDoc.ErrorRow(), m_xmlDoc.ErrorDesc());
    return false;
  }

  m_dlgProgress->Close();

  return true;
}

void CLastFMDirectory::AddEntry(int iString, CStdString strPath, CStdString strIconPath, bool bFolder, CFileItemList &items)
{
  CStdString strLabel = g_localizeStrings.Get(iString);
  strLabel.Replace("%name%", m_objname);
  strLabel.Replace("%type%", m_objtype);
  strLabel.Replace("%request%", m_objrequest);
  strPath.Replace("%name%", m_encodedobjname);
  strPath.Replace("%type%", m_objtype);
  strPath.Replace("%request%", m_objrequest);

  CFileItemPtr pItem(new CFileItem);
  pItem->SetLabel(strLabel);
  pItem->SetPath(strPath);
  pItem->m_bIsFolder = bFolder;
  pItem->SetLabelPreformated(true);
  //the extra info is used in the mediawindows to determine which items are needed in the contextmenu
  if (strPath.Find("lastfm://xbmc") >= 0)
  {
    pItem->SetCanQueue(false);
    pItem->SetExtraInfo("lastfmitem");
  }

  items.Add(pItem);
}

void CLastFMDirectory::AddListEntry(const char *name, const char *artist, const char *count, const char *date, const char *icon, CStdString strPath, CFileItemList &items)
{
  CStdString strName;
  CFileItemPtr pItem(new CFileItem);
  CMusicInfoTag* musicinfotag = pItem->GetMusicInfoTag();
  musicinfotag->SetTitle(name);

  if (artist)
  {
    strName.Format("%s - %s", artist, name);
    musicinfotag->SetArtist(artist);
  }
  else
  {
    strName = name;
  }

  if (count)
  {
    pItem->SetLabel2(count);
    pItem->m_dwSize = _atoi64(count) * 100000000;

    const char *dot;
    if ((dot = (const char *)strstr(count, ".")))
      pItem->m_dwSize += _atoi64(dot + 1);
  }

  pItem->SetLabel(strName);
  pItem->SetPath(strPath);
  pItem->m_bIsFolder = true;
  pItem->SetLabelPreformated(true);

  if (date)
  {
    LONGLONG ll = Int32x32To64(atoi(date), 10000000) + 116444736000000000LL;
    FILETIME ft;

    ft.dwLowDateTime = (DWORD)(ll & 0xFFFFFFFF);
    ft.dwHighDateTime = (DWORD)(ll >> 32);

    pItem->m_dateTime=ft;
  }

  pItem->SetCanQueue(false);
  //the extra info is used in the mediawindows to determine which items are needed in the contextmenu
  if (m_objname.Equals(g_guiSettings.GetString("scrobbler.lastfmusername")))
  {
    if (m_objrequest.Equals("recentbannedtracks"))
    {
      pItem->SetExtraInfo("lastfmbanned");
    }
    else if (m_objrequest.Equals("recentlovedtracks"))
    {
      pItem->SetExtraInfo("lastfmloved");
    }
  }
  if (pItem->GetExtraInfo().IsEmpty() && strPath.Find("lastfm://xbmc") >= 0)
  {
    pItem->SetExtraInfo("lastfmitem");
  }

  // icons? would probably take too long to retrieve them all
  items.Add(pItem);
}

bool CLastFMDirectory::ParseArtistList(CStdString url, CFileItemList &items)
{
  if (!RetrieveList(url))
    return false;

  TiXmlElement* pRootElement = m_xmlDoc.RootElement();

  TiXmlElement* pEntry = pRootElement->FirstChildElement("artist");

  while(pEntry)
  {
    TiXmlNode* name = pEntry->FirstChild("name");
    TiXmlNode* count;
    const char *countstr = NULL;
    const char *namestr = NULL;

    count = pEntry->FirstChild("count");
    if (!count) count = pEntry->FirstChild("playcount");
    if (!count) count = pEntry->FirstChild("match");
    if (!count && pEntry->Attribute("count"))
      countstr = pEntry->Attribute("count");
    else
      countstr = count->FirstChild()->Value();
    if (name)
      namestr = name->FirstChild()->Value();
    else
      namestr = pEntry->Attribute("name");


    if (namestr)
      AddListEntry(namestr, NULL, countstr, NULL, NULL,
          "lastfm://root/artist/" + (CStdString)namestr + "/", items);

    pEntry = pEntry->NextSiblingElement("artist");
  }

  m_xmlDoc.Clear();
  return true;
}

bool CLastFMDirectory::ParseAlbumList(CStdString url, CFileItemList &items)
{
  if (!RetrieveList(url))
    return false;

  TiXmlElement* pRootElement = m_xmlDoc.RootElement();

  TiXmlElement* pEntry = pRootElement->FirstChildElement("album");

  while(pEntry)
  {
    const char *artist = pRootElement->Attribute("artist");
    const char *name = NULL;
    const char *count = NULL;

    if (pEntry->Attribute("name"))
      name = pEntry->Attribute("name");
    else
    {
      TiXmlNode* nameNode = pEntry->FirstChild("name");
      if (nameNode && nameNode->FirstChild())
        name = nameNode->FirstChild()->Value();
    }

    TiXmlElement* artistElement = pEntry->FirstChildElement("artist");
    if (artistElement && artistElement->Attribute("name"))
      artist = artistElement->Attribute("name");
    else
    {
      if (artistElement && artistElement->FirstChild())
        artist = artistElement->FirstChild()->Value();
    }

    if (pEntry->Attribute("count"))
      count = pEntry->Attribute("count");
    else
    {
      TiXmlNode* countNode = pEntry->FirstChild("count");
      if (!countNode) countNode = pEntry->FirstChild("playcount");
      if (!countNode) countNode = pEntry->FirstChild("reach");
      if (countNode)
        count = countNode->FirstChild()->Value();
    }

    AddListEntry(name, artist, count, NULL, NULL,
        "lastfm://root/artist/" + (CStdString)artist + "/", items);

    pEntry = pEntry->NextSiblingElement("album");
  }

  m_xmlDoc.Clear();
  return true;
}

bool CLastFMDirectory::ParseUserList(CStdString url, CFileItemList &items)
{
  if (!RetrieveList(url))
    return false;

  TiXmlElement* pRootElement = m_xmlDoc.RootElement();

  TiXmlElement* pEntry = pRootElement->FirstChildElement("user");

  while(pEntry)
  {
    const char *name = pEntry->Attribute("username");

    TiXmlNode* count;
    count = pEntry->FirstChild("weight");
    if (!count) count = pEntry->FirstChild("match");

    if (name)
    {
      AddListEntry(name, NULL, (count && count->FirstChild()) ? count->FirstChild()->Value() : NULL, NULL, NULL,
          "lastfm://root/user/" + (CStdString)name + "/", items);
    }

    pEntry = pEntry->NextSiblingElement("user");
  }

  m_xmlDoc.Clear();
  return true;
}

bool CLastFMDirectory::ParseTagList(CStdString url, CFileItemList &items)
{
  if (!RetrieveList(url))
    return false;

  TiXmlElement* pRootElement = m_xmlDoc.RootElement();

  TiXmlElement* pEntry = pRootElement->FirstChildElement("tag");

  while(pEntry)
  {
    TiXmlNode* name = pEntry->FirstChild("name");
    TiXmlNode* count;
    const char *countstr = NULL;
    const char *namestr = NULL;

    count = pEntry->FirstChild("count");
    if (!count) count = pEntry->FirstChild("playcount");
    if (!count) count = pEntry->FirstChild("match");
    if (!count && pEntry->Attribute("count"))
      countstr = pEntry->Attribute("count");
    else if (count->FirstChild())
      countstr = count->FirstChild()->Value();

    if (name && name->FirstChild())
      namestr = name->FirstChild()->Value();
    else
      namestr = pEntry->Attribute("name");

    if (namestr)
    {
      AddListEntry(namestr, NULL, countstr, NULL, NULL,
          "lastfm://root/tag/" + (CStdString)namestr + "/", items);
    }

    pEntry = pEntry->NextSiblingElement("tag");
  }

  m_xmlDoc.Clear();
  return true;
}

bool CLastFMDirectory::ParseTrackList(CStdString url, CFileItemList &items)
{
  if (!RetrieveList(url))
    return false;

  TiXmlElement* pRootElement = m_xmlDoc.RootElement();

  TiXmlElement* pEntry = pRootElement->FirstChildElement("track");

  while(pEntry)
  {
    TiXmlNode* name = pEntry->FirstChild("name");
    TiXmlNode* artist = pEntry->FirstChild("artist");
    TiXmlElement *date = pEntry->FirstChildElement("date");

    TiXmlNode* count;
    count = pEntry->FirstChild("count");
    if (!count) count = pEntry->FirstChild("playcount");
    if (!count) count = pEntry->FirstChild("match");

    if (name)
    {
      if (artist)
        AddListEntry((name) ? name->FirstChild()->Value() : NULL,
            (artist) ? artist->FirstChild()->Value() : NULL,
            (count) ? count->FirstChild()->Value() : ((date) ? date->FirstChild()->Value() : NULL),
            (date) ? date->Attribute("uts") : NULL,
            NULL, "lastfm://root/artist/" + (CStdString)artist->FirstChild()->Value() + "/", items);
      else
        // no artist in xml, assuming we're retrieving track list for the artist in m_objname...
        AddListEntry((name) ? name->FirstChild()->Value() : NULL,
            m_objname.c_str(),
            (count) ? count->FirstChild()->Value() : NULL,
            NULL, NULL, "lastfm://root/artist/" + m_objname + "/", items);
    }
    else
    {
      // no luck, try another way :)
      const char *name = pEntry->Attribute("name");
      const char *artist = pEntry->FirstChildElement("artist")->Attribute("name");
      const char *count = pEntry->Attribute("count");

      if (name)
        AddListEntry(name, artist, count, NULL, NULL,
            "lastfm://root/artist/" + (CStdString)artist + "/", items);
    }

    pEntry = pEntry->NextSiblingElement("track");
  }

  m_xmlDoc.Clear();
  return true;
}

bool CLastFMDirectory::SearchSimilarArtists(CFileItemList &items)
{
  CStdString strSearchTerm = "";

  if (!GetKeyboardInput(15281, strSearchTerm))
    return false;

  m_objname = m_encodedobjname = strSearchTerm;
  CURL::Encode(m_encodedobjname);
  CURL::Decode(m_objname);

  AddEntry(15267, "lastfm://artist/%name%/similarartists", "", false, items);
  return ParseArtistList(BuildURLFromInfo(), items);
}

bool CLastFMDirectory::SearchSimilarTags(CFileItemList &items)
{
  CStdString strSearchTerm = "";

  if (!GetKeyboardInput(15282, strSearchTerm))
    return false;

  m_objname = m_encodedobjname = strSearchTerm;
  CURL::Encode(m_encodedobjname);
  CURL::Decode(m_objname);

  return ParseTagList(BuildURLFromInfo(), items);
}

bool CLastFMDirectory::GetArtistInfo(CFileItemList &items)
{
  if (m_objname == "*" && m_objrequest == "similar")
    return SearchSimilarArtists(items);

  if (m_objrequest == "similar")
    return ParseArtistList(BuildURLFromInfo(), items);
  else if (m_objrequest == "topalbums")
    return ParseAlbumList(BuildURLFromInfo(), items);
  else if (m_objrequest == "toptracks")
    return ParseTrackList(BuildURLFromInfo(), items);
  else if (m_objrequest == "toptags")
    return ParseTagList(BuildURLFromInfo(), items);
  else if (m_objrequest == "fans")
    return ParseUserList(BuildURLFromInfo(), items);
  else if (m_objrequest == "")
  {
    AddEntry(15261, "lastfm://root/artist/%name%/similar/", "", true, items);
    AddEntry(15262, "lastfm://root/artist/%name%/topalbums/", "", true, items);
    AddEntry(15263, "lastfm://root/artist/%name%/toptracks/", "", true, items);
    AddEntry(15264, "lastfm://root/artist/%name%/toptags/", "", true, items);
    AddEntry(15265, "lastfm://root/artist/%name%/fans/", "", true, items);
    AddEntry(15266, "lastfm://artist/%name%/fans", "", false, items);
    AddEntry(15267, "lastfm://artist/%name%/similarartists", "", false, items);
  }
  else
    return false;

  return true;
}

bool CLastFMDirectory::GetUserInfo(CFileItemList &items)
{
  if (m_objrequest == "topartists")
    return ParseArtistList(BuildURLFromInfo(), items);
  else if (m_objrequest == "topalbums")
    return ParseAlbumList(BuildURLFromInfo(), items);
  else if (m_objrequest == "toptracks")
    return ParseTrackList(BuildURLFromInfo(), items);
  else if (m_objrequest == "toptags")
    return ParseTagList(BuildURLFromInfo(), items);
  else if (m_objrequest == "tags")
    return ParseTagList(BuildURLFromInfo(), items);
  else if (m_objrequest == "friends")
    return ParseUserList(BuildURLFromInfo(), items);
  else if (m_objrequest == "neighbours")
    return ParseUserList(BuildURLFromInfo(), items);
  else if (m_objrequest == "weeklyartistchart")
    return ParseArtistList(BuildURLFromInfo(), items);
  else if (m_objrequest == "weeklyalbumchart")
    return ParseAlbumList(BuildURLFromInfo(), items);
  else if (m_objrequest == "weeklytrackchart")
    return ParseTrackList(BuildURLFromInfo(), items);
  else if (m_objrequest == "recenttracks")
    return ParseTrackList(BuildURLFromInfo(), items);
  else if (m_objrequest == "recentlovedtracks")
    return ParseTrackList(BuildURLFromInfo(), items);
  else if (m_objrequest == "recentbannedtracks")
    return ParseTrackList(BuildURLFromInfo(), items);
  else if (m_objrequest == "")
  {
    AddEntry(15268, "lastfm://root/user/%name%/topartists/", "", true, items);
    AddEntry(15269, "lastfm://root/user/%name%/topalbums/", "", true, items);
    AddEntry(15270, "lastfm://root/user/%name%/toptracks/", "", true, items);
    AddEntry(15285, "lastfm://root/user/%name%/tags/", "", true, items);
    AddEntry(15271, "lastfm://root/user/%name%/friends/", "", true, items);
    AddEntry(15272, "lastfm://root/user/%name%/neighbours/", "", true, items);
    AddEntry(15273, "lastfm://root/user/%name%/weeklyartistchart/", "", true, items);
    AddEntry(15274, "lastfm://root/user/%name%/weeklyalbumchart/", "", true, items);
    AddEntry(15275, "lastfm://root/user/%name%/weeklytrackchart/", "", true, items);
    AddEntry(15283, "lastfm://root/user/%name%/recenttracks/", "", true, items);
    AddEntry(15293, "lastfm://root/user/%name%/recentlovedtracks/", "", true, items);
    AddEntry(15294, "lastfm://root/user/%name%/recentbannedtracks/", "", true, items);
    AddEntry(15276, "lastfm://user/%name%/neighbours", "", false, items);
    AddEntry(15277, "lastfm://user/%name%/personal", "", false, items);
    AddEntry(15284, "lastfm://user/%name%/recommended/100", "", false, items);
    AddEntry(15278, "lastfm://user/%name%/mix", "", false, items);
  }
  else
    return false;

  return true;
}

bool CLastFMDirectory::GetTagInfo(CFileItemList &items)
{
  if (m_objname == "*" && m_objrequest== "search")
    return SearchSimilarTags(items);

  if (m_objrequest == "topartists")
    return ParseArtistList(BuildURLFromInfo(), items);
  else if (m_objrequest == "topalbums")
    return ParseAlbumList(BuildURLFromInfo(), items);
  else if (m_objrequest == "toptracks")
    return ParseTrackList(BuildURLFromInfo(), items);
  else if (m_objrequest == "toptags")
    return ParseTagList(BuildURLFromInfo(), items);
  else if (m_objrequest == "")
  {
    AddEntry(15257, "lastfm://root/tag/%name%/topartists/", "", true, items);
    AddEntry(15258, "lastfm://root/tag/%name%/topalbums/", "", true, items);
    AddEntry(15259, "lastfm://root/tag/%name%/toptracks/", "", true, items);
    AddEntry(15260, "lastfm://globaltags/%name%", "", false, items);
  }

  return true;
}

bool CLastFMDirectory::GetDirectory(const CStdString& strPath, CFileItemList &items)
{
  CStdString strURL = strPath;
  CURL url(strURL);
  strURL=url.GetFileName();

  // parse the URL, finding object type, name, and requested info
  CStdStringArray vecURLParts;

  m_objtype = "";
  m_objname = "";
  m_objrequest = "";

  switch(StringUtils::SplitString(strURL, "/", vecURLParts))
  {
  case 1:
    // simple lastfm:// root URL...
    g_directoryCache.ClearSubPaths("lastfm://");
    break;
  // the following fallthru's are on purpose
  case 5:
    m_objrequest = vecURLParts[3];
  case 4:
    m_objname = vecURLParts[2];
    m_encodedobjname = vecURLParts[2];
    CURL::Encode(m_encodedobjname);
    CURL::Decode(m_objname);
  case 3:
    m_objtype = vecURLParts[1];
  case 2:
    if (vecURLParts[0] != "xbmc")
      return false;
    break;
  default:
    return false;
  }

  if (m_objtype == "user")
    m_Error = GetUserInfo(items);
  else if (m_objtype == "tag")
    m_Error = GetTagInfo(items);
  else if (m_objtype == "artist")
    m_Error = GetArtistInfo(items);
  else if (m_objtype == "")
  {
    AddEntry(15253, "lastfm://root/artist/*/similar/", "", true, items);
    AddEntry(15254, "lastfm://root/tag/*/search/", "", true, items);
    AddEntry(15256, "lastfm://root/tag/root/toptags/", "", true, items);
    if (g_guiSettings.GetString("scrobbler.lastfmusername") != "")
    {
      m_encodedobjname = m_objname = g_guiSettings.GetString("scrobbler.lastfmusername");
      CURL::Decode(m_encodedobjname);
      AddEntry(15255, "lastfm://root/user/%name%/", "", true, items);
    }
    return true;
  }
  else
    return false;

  return m_Error;
}

DIR_CACHE_TYPE CLastFMDirectory::GetCacheType(const CStdString& strPath) const
{
  if (strPath == "lastfm://")
    return DIR_CACHE_ONCE;
  return DIR_CACHE_ALWAYS;
}

void CLastFMDirectory::Run()
{
  XFILE::CFileCurl http;
  if (!http.Download(m_strSource, m_strDestination))
    m_Error=true;

  m_Downloaded=true;
}
