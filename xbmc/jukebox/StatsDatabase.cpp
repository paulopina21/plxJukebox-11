#include "StatsDatabase.h"
#include "utils/log.h"
#include "utils/StringUtils.h"
//#include "utils/AutoPtrHandle.h"
#include "dbwrappers/dataset.h"
#include "utils/XMLUtils.h"

#include "FileItem.h"
#include "../music/tags/MusicInfoTag.h"

#include "dialogs/GUIDialogProgress.h"
#include "dialogs/GUIDialogOK.h"

#include "guilib/GUIWindowManager.h"

using namespace std;
//using namespace AUTOPTR;
//using namespace dbiplus;
//using namespace XFILE;


CStatsDatabase::CStatsDatabase(): CDatabase() {
}

CStatsDatabase::~CStatsDatabase() {
}

bool CStatsDatabase::Open() {
  return CDatabase::Open();
}

bool CStatsDatabase::CommitTransaction() {
  return CDatabase::CommitTransaction();
}

CStdString CStatsDatabase::GetABLFReport(bool bRecoverLast) {
  Open();
  if (NULL == m_pDB.get()) return "";
  if (NULL == m_pDS.get()) return "";

  CStdString strOrderBy = "ORDER BY log.strTimeStamp LIMIT 1";

  if (bRecoverLast)
    strOrderBy = "ORDER BY log.idEntry DESC LIMIT 1";

  CStdString strSQL = PrepareSQL("SELECT strArtist, strAlbum, strTitle, strLabel, song.strTimeStamp FROM song "
  "JOIN (select log.strTimeStamp from log where log.idActivity = %i %s) "
  "AS log WHERE datetime(song.strTimeStamp) > datetime(log.strTimestamp)", ACTIVITY_SONGS_LAST_REPORT, strOrderBy.c_str());

  m_pDS->query(strSQL.c_str());

  int total = m_pDS->num_rows();
  int current = 0;

  CGUIDialogOK *dlgResult = (CGUIDialogOK *)g_windowManager.GetWindow(WINDOW_DIALOG_OK);
  if (!dlgResult) {
    CLog::Log(LOGERROR,"%s: ERROR CREATING DIALOG", __FUNCTION__);
    return "";
  }

  if (total <= 0) {
    dlgResult->ShowAndGetInput(70002,70009,-1,-1);
    return "";
  }

  CGUIDialogProgress *progress = (CGUIDialogProgress *)g_windowManager.GetWindow(WINDOW_DIALOG_PROGRESS);
  if (!progress) {
    CLog::Log(LOGERROR,"%s: ERROR CREATING DIALOG", __FUNCTION__);
    return "";
  }

  progress->SetHeading(70002);
  progress->SetLine(0, 650);
  progress->SetLine(1, "");
  progress->SetLine(2, "");
  progress->SetPercentage(0);
  progress->StartModal();
  progress->ShowProgressBar(true);

  // create our xml document
  TiXmlDocument xmlDoc;
  TiXmlDeclaration decl("1.0", "UTF-8", "yes");
  xmlDoc.InsertEndChild(decl);
  TiXmlNode *pMain = NULL;
  pMain = &xmlDoc;

  TiXmlElement gradeElement("Grade");
  TiXmlNode* trackNode = pMain->InsertEndChild(gradeElement);

  while (!m_pDS->eof())
  {
    TiXmlElement musicElement("Musica");
    musicElement.SetAttribute("id",current +1);
    TiXmlNode* musicNode = trackNode->InsertEndChild(musicElement);

    CStdString strArtist    = m_pDS->fv("strArtist").get_asString();
    CStdString strAlbum     = m_pDS->fv("strAlbum").get_asString();
    CStdString strTitle     = m_pDS->fv("strTitle").get_asString();
    CStdString strLabel     = m_pDS->fv("strLabel").get_asString();
    CStdString strTimeStamp = m_pDS->fv("strTimeStamp").get_asString();

    CStdString strDate = strTimeStamp.substr(0,10);
    CStdString strTime = strTimeStamp.substr(11,8);

    XMLUtils::SetString(musicNode,"Nome", strTitle);
    XMLUtils::SetString(musicNode,"Artista", strArtist);
    XMLUtils::SetString(musicNode,"Gravadora", strLabel);
//    XMLUtils::SetString(musicNode,"Album", strAlbum);
    XMLUtils::SetString(musicNode,"Data", strDate);
    XMLUtils::SetString(musicNode,"Hora", strTime);

    //progress->SetLine(1, album.strAlbum);
    progress->SetPercentage(current * 100 / total);
    progress->Progress();
    if (progress->IsCanceled())
    {
      progress->Close();
      Close();
      return "";
    }
    m_pDS->next();
    current++;
  }

  TiXmlPrinter xmlPrinter;
  xmlPrinter.SetIndent( "  " );

  xmlDoc.Accept( &xmlPrinter );
  CStdString strXmlText = xmlPrinter.CStr();

  progress->SetPercentage(current * 100 / total);
  progress->Close();
  Close();

  return strXmlText;
}

CStdString CStatsDatabase::GetAdvertisingReport(bool bRecoverLast) {
  Open();
  if (NULL == m_pDB.get()) return "";
  if (NULL == m_pDS.get()) return "";

  CStdString strOrderBy = "ORDER BY log.strTimeStamp LIMIT 1";

  if (bRecoverLast)
    strOrderBy = "ORDER BY log.idEntry DESC LIMIT 1";

  CStdString strSQL = PrepareSQL("SELECT idAdvertising, advertising.strTimeStamp FROM advertising "
  "JOIN (select log.strTimeStamp from log where log.idActivity = %i %s) "
  "AS log WHERE datetime(advertising.strTimeStamp) > datetime(log.strTimestamp)", ACTIVITY_ADVERT_LAST_REPORT, strOrderBy.c_str());

  m_pDS->query(strSQL.c_str());

  int total = m_pDS->num_rows();
  int current = 0;

  CGUIDialogOK *dlgResult = (CGUIDialogOK *)g_windowManager.GetWindow(WINDOW_DIALOG_OK);
  if (!dlgResult) {
    CLog::Log(LOGERROR,"%s: ERROR CREATING DIALOG", __FUNCTION__);
    return "";
  }

  if (total <= 0) {
    dlgResult->ShowAndGetInput(70003,70009,-1,-1);
    return "";
  }

  CGUIDialogProgress *progress = (CGUIDialogProgress *)g_windowManager.GetWindow(WINDOW_DIALOG_PROGRESS);
  if (!progress) {
    CLog::Log(LOGERROR,"%s: ERROR CREATING DIALOG", __FUNCTION__);
    return "";
  }

  progress->SetHeading(70003);
  progress->SetLine(0, 650);
  progress->SetLine(1, "");
  progress->SetLine(2, "");
  progress->SetPercentage(0);
  progress->StartModal();
  progress->ShowProgressBar(true);

  // create our xml document
  TiXmlDocument xmlDoc;
  TiXmlDeclaration decl("1.0", "UTF-8", "yes");
  xmlDoc.InsertEndChild(decl);
  TiXmlNode *pMain = NULL;
  pMain = &xmlDoc;

  TiXmlElement gradeElement("Grade");
  TiXmlNode* gradeNode = pMain->InsertEndChild(gradeElement);

  while (!m_pDS->eof())
  {
    TiXmlElement advertElement("Propaganda");
    advertElement.SetAttribute("id",current +1);
    TiXmlNode* advertNode = gradeNode->InsertEndChild(advertElement);

    int idAdversiting = m_pDS->fv("idAdvertising").get_asInt();
    CStdString strTimeStamp = m_pDS->fv("strTimeStamp").get_asString();

    CStdString strDate = strTimeStamp.substr(0,10);
    CStdString strTime = strTimeStamp.substr(11,5);

    XMLUtils::SetInt(advertNode,"ID", idAdversiting);
    XMLUtils::SetString(advertNode,"Data", strDate);
    XMLUtils::SetString(advertNode,"Hora", strTime);

    progress->SetPercentage(current * 100 / total);
    progress->Progress();
    if (progress->IsCanceled())
    {
      progress->Close();
      Close();
      return "";
    }
    m_pDS->next();
    current++;
  }

  TiXmlPrinter xmlPrinter;
  xmlPrinter.SetIndent( "  " );

  xmlDoc.Accept( &xmlPrinter );
  CStdString strXmlText = xmlPrinter.CStr();

  progress->SetPercentage(current * 100 / total);
  progress->Close();
  Close();

  return strXmlText;
}

bool CStatsDatabase::UpdateOldVersion( int version ) {
  return true;
}

void CStatsDatabase::CreateViews() {
  CLog::Log(LOGINFO, "No views avaiable in Stats database...");
}


bool CStatsDatabase::CreateTables() {
  if (NULL == m_pDB.get()) return false;
  if (NULL == m_pDS.get()) return false;

  CDatabase::BeginTransaction();
  try	{
    CDatabase::CreateTables();

    CLog::Log(LOGINFO, "StatsDatabase: creating songs table");
    m_pDS->exec("CREATE TABLE song (id INTEGER PRIMARY KEY, idSong INTEGER, strArtist TEXT, strAlbum TEXT, strTitle TEXT, strLabel TEXT, strTimeStamp TEXT DEFAULT (datetime('now','localtime')) )\n");

    CLog::Log(LOGINFO, "StatsDatabase: creating video table");
    m_pDS->exec("CREATE TABLE video (id INTEGER PRIMARY KEY, idVideo INTEGER, strArtist TEXT, strAlbum TEXT, strTitle TEXT, strLabel TEXT, strTimeStamp TEXT DEFAULT (datetime('now','localtime')) )\n");

    CLog::Log(LOGINFO, "StatsDatabase: creating advertising table");
    m_pDS->exec("CREATE TABLE advertising (id INTEGER PRIMARY KEY, idAdvertising INTEGER, strTitle TEXT, strTimeStamp TEXT DEFAULT (datetime('now','localtime')))\n");

    CLog::Log(LOGINFO, "StatsDatabase: creating coins table");
    m_pDS->exec("CREATE TABLE coins (idCoin INTEGER PRIMARY KEY, strTimeStamp TEXT DEFAULT (datetime('now','localtime')) )\n");

    CLog::Log(LOGINFO, "StatsDatabase: creating log table");
    m_pDS->exec("CREATE TABLE log (idEntry INTEGER PRIMARY KEY, idActivity INTEGER, strTimeStamp TEXT DEFAULT (datetime('now','localtime')) )\n");

    CLog::Log(LOGINFO, "StatsDatabase: creating genre table");
    m_pDS->exec("CREATE TABLE genre (id INTEGER PRIMARY KEY, strGenre varchar(256), idTimesPlayed INTEGER DEFAULT 1)\n");
    //SELECT strArtist, strAlbum, strTitle, strLabel, song.strTimeStamp FROM song
    //JOIN log ON log.idActivity = 1
    //WHERE datetime(song.strTimeStamp) > datetime(log.strTimestamp)

    //CLog::Log(LOGINFO, "create professional index");
    //m_pDS->exec("CREATE INDEX idxProfessional ON professional(id)");

    //CLog::Log(LOGINFO, "create coinslog table");
    //m_pDS->exec("CREATE TABLE coinslog (id integer primary key, strWhen text, coins integer)\n");

    //CLog::Log(LOGINFO, "create coinslog index");
    //m_pDS->exec("CREATE UNIQUE INDEX idxCoinslog ON coinslog(id)");

    //m_pDS->exec("INSERT INTO professional (id, coins, prepaid, total, cont) VALUES(0,0,0,0,0)\n");
    //m_pDS->post();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s unable to create tables, Rollbacking transaction.", __FUNCTION__);
    RollbackTransaction();
    return false;
  }
  CommitTransaction();
  return true;
}

bool CStatsDatabase::ExportABLFReport(const CStdString& strPath, bool bRecoverLast){
  Open();
  if (NULL == m_pDB.get()) return false;
  if (NULL == m_pDS.get()) return false;

  CStdString strOrderBy = "ORDER BY log.strTimeStamp LIMIT 1";

  if (bRecoverLast)
    strOrderBy = "ORDER BY log.idEntry DESC LIMIT 1";

  CStdString strSQL = PrepareSQL("SELECT strArtist, strAlbum, strTitle, strLabel, song.strTimeStamp FROM song "
  "JOIN (select log.strTimeStamp from log where log.idActivity = %i %s) "
  "AS log WHERE datetime(song.strTimeStamp) > datetime(log.strTimestamp)", ACTIVITY_SONGS_LAST_REPORT, strOrderBy.c_str());

  m_pDS->query(strSQL.c_str());

  int total = m_pDS->num_rows();
  int current = 0;

  CGUIDialogOK *dlgResult = (CGUIDialogOK *)g_windowManager.GetWindow(WINDOW_DIALOG_OK);
  if (!dlgResult) {
    CLog::Log(LOGERROR,"%s: ERROR CREATING DIALOG", __FUNCTION__);
    return false;
  }

  if (total <= 0) {
    dlgResult->ShowAndGetInput(70002,70009,-1,-1);
    return false;
  }

  CGUIDialogProgress *progress = (CGUIDialogProgress *)g_windowManager.GetWindow(WINDOW_DIALOG_PROGRESS);
  if (!progress) {
    CLog::Log(LOGERROR,"%s: ERROR CREATING DIALOG", __FUNCTION__);
    return false;
  }

  progress->SetHeading(70002);
  progress->SetLine(0, 650);
  progress->SetLine(1, "");
  progress->SetLine(2, "");
  progress->SetPercentage(0);
  progress->StartModal();
  progress->ShowProgressBar(true);

  // create our xml document
  TiXmlDocument xmlDoc;
  TiXmlDeclaration decl("1.0", "UTF-8", "yes");
  xmlDoc.InsertEndChild(decl);
  TiXmlNode *pMain = NULL;
  pMain = &xmlDoc;

  TiXmlElement gradeElement("Grade");
  TiXmlNode* trackNode = pMain->InsertEndChild(gradeElement);

  while (!m_pDS->eof())
  {
    TiXmlElement musicElement("Musica");
    musicElement.SetAttribute("id",current +1);
    TiXmlNode* musicNode = trackNode->InsertEndChild(musicElement);

    CStdString strArtist    = m_pDS->fv("strArtist").get_asString();
    CStdString strAlbum     = m_pDS->fv("strAlbum").get_asString();
    CStdString strTitle     = m_pDS->fv("strTitle").get_asString();
    CStdString strLabel     = m_pDS->fv("strLabel").get_asString();
    CStdString strTimeStamp = m_pDS->fv("strTimeStamp").get_asString();

    CStdString strDate = strTimeStamp.substr(0,10);
    CStdString strTime = strTimeStamp.substr(11,8);

    XMLUtils::SetString(musicNode,"Nome", strTitle);
    XMLUtils::SetString(musicNode,"Artista", strArtist);
    XMLUtils::SetString(musicNode,"Gravadora", strLabel);
//    XMLUtils::SetString(musicNode,"Album", strAlbum);
    XMLUtils::SetString(musicNode,"Data", strDate);
    XMLUtils::SetString(musicNode,"Hora", strTime);

    //progress->SetLine(1, album.strAlbum);
    progress->SetPercentage(current * 100 / total);
    progress->Progress();
    if (progress->IsCanceled())
    {
      progress->Close();
      Close();
      return false;
    }
    m_pDS->next();
    current++;
  }

  bool bFileSaved = xmlDoc.SaveFile(strPath);

  progress->SetPercentage(current * 100 / total);
  progress->Close();
  Close();

  if (!bFileSaved) {
    dlgResult->ShowAndGetInput(70002,70010,70011,-1);
    return false;
  }

  dlgResult->ShowAndGetInput(70002,70008,-1,-1);
  return true;
}

bool CStatsDatabase::LogPlayedItem(CFileItem* pItem) {
  try	{
    Open();
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;

    CStdString strArtist = pItem->GetMusicInfoTag()->GetArtist();
    CStdString strAlbum = pItem->GetMusicInfoTag()->GetAlbum();
    CStdString strTitle = pItem->GetMusicInfoTag()->GetTitle();
    CStdString strLabel = pItem->GetMusicInfoTag()->GetLabel();
    CStdString strGenre = pItem->GetMusicInfoTag()->GetGenre();

    if(strArtist.empty() || strAlbum.empty() || strTitle.empty() || strLabel.empty() || strGenre.empty()) {
      Close();
      return false;
    }


    CStdString strSQL;

    if (pItem->IsAudio())
    {
      strSQL = PrepareSQL("INSERT INTO song(idSong, strArtist, strAlbum, strTitle, strLabel) VALUES(0, '%s', '%s', '%s', '%s')", strArtist.c_str(), strAlbum.c_str(), strTitle.c_str(), strLabel.c_str());
      m_pDS->exec(strSQL.c_str());
    }
    else
    if (pItem->IsVideo())
    {
      strSQL = PrepareSQL("INSERT INTO video(idVideo, strArtist, strAlbum, strTitle, strLabel) VALUES(0, '%s', '%s', '%s', '%s')", strArtist.c_str(), strAlbum.c_str(), strTitle.c_str(), strLabel.c_str());
      m_pDS->exec(strSQL.c_str());
    }

     strSQL = PrepareSQL("SELECT id FROM genre where strGenre = '%s' ", strGenre.c_str());
    m_pDS->query(strSQL.c_str());

    if (m_pDS->num_rows() >0) {
      int id = m_pDS->fv("id").get_asInt();
      int iTimesPlayed = m_pDS->fv("iTimesPlayed").get_asInt();

      strSQL = PrepareSQL("UPDATE genre SET iTimesPlayed = %i WHERE id = %i", iTimesPlayed +1, id);
    }
    else {
      strSQL = PrepareSQL("INSERT INTO genre(strGenre) VALUES('%s')", strGenre.c_str());
      m_pDS->exec(strSQL.c_str());
    }
    Close();
    return true;
  }
  catch (...)	{
    CLog::Log(LOGERROR, "%s failed on adding media stat", __FUNCTION__);
  }
  Close();
  return false;
}
