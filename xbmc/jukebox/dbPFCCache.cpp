#include "dbPFCCache.h"
#include "utils/log.h"
#include "utils/StringUtils.h"
#include "../URL.h"
//#include "utils/AutoPtrHandle.h"
#include "dbwrappers/dataset.h"

#include "FileItem.h"
#include "../music/tags/MusicInfoTag.h"

using namespace std;
//using namespace AUTOPTR;
//using namespace dbiplus;
//using namespace XFILE;


dbPFCCache::dbPFCCache(): CDatabase() {
}

dbPFCCache::~dbPFCCache() {
}

bool dbPFCCache::Open() {
  return CDatabase::Open();
}

bool dbPFCCache::CommitTransaction() {
  return CDatabase::CommitTransaction();
}

bool dbPFCCache::UpdateOldVersion( int version ) {
  return true;
}

void dbPFCCache::CreateViews() {
  CLog::Log(LOGINFO, "No views avaiable in Stats database...");
}


bool dbPFCCache::CreateTables() {
  if (NULL == m_pDB.get()) return false;
  if (NULL == m_pDS.get()) return false;

  CDatabase::BeginTransaction();
  try	{
    CDatabase::CreateTables();

    CLog::Log(LOGINFO, "dbPFCCahe: Creating paths table");
    m_pDS->exec("CREATE TABLE path (idPath INTEGER PRIMARY KEY, strPath varchar(512), strHash TEXT, strTimeStamp TEXT DEFAULT (datetime('now','localtime')) )\n");

    CLog::Log(LOGINFO, "dbPFCCahe: Creating files table");
    m_pDS->exec("CREATE TABLE file (idFile INTEGER PRIMARY KEY, idPath INTEGER, strFileName varchar(512), strTimeStamp TEXT DEFAULT (datetime('now','localtime')) )\n");

    CLog::Log(LOGINFO, "dbPFCCahe: Creating path index");
    m_pDS->exec("CREATE INDEX idxPath ON path(idPath)");

    CLog::Log(LOGINFO, "dbPFCCahe: Creating files index");
    m_pDS->exec("CREATE INDEX idxFile ON file(idFile)");

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

int dbPFCCache::AddPath(const CStdString& strPath) {
  if (NULL == m_pDB.get()) return false;
  if (NULL == m_pDS.get()) return false;

  try {
    CStdString strSQL=PrepareSQL("SELECT idPath FROM path WHERE strPath LIKE '%s'", strPath.c_str());
    m_pDS->query(strSQL.c_str());

    if (m_pDS->num_rows() > 0)
      return m_pDS->fv("idPath").get_asInt();

  } catch (...) {
    CLog::Log(LOGERROR, "dbPFCCache: Failed: AddPath(%s)", strPath.c_str());
    return -1;
  }

  CDatabase::BeginTransaction();
  try
  {
    CStdString strSQL=PrepareSQL("INSERT INTO path(strPath) VALUES('%s')\n", strPath.c_str());
    m_pDS->exec(strSQL.c_str());
    m_pDS->post();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "dbPFCCache: Failed adding path to cache: %s", strPath.c_str());
    RollbackTransaction();
    return -1;
  }
  CommitTransaction();
  return (int)m_pDS->lastinsertid();
}

int dbPFCCache::AddFile(const CStdString& strFullFilePath) {
  if (NULL == m_pDB.get()) return false;
  if (NULL == m_pDS.get()) return false;

  CURL strURL(strFullFilePath);
  CStdString strPath = strURL.GetWithoutFilename();
  CStdString strFileName = strURL.GetFileNameWithoutPath();

  try {
    CStdString strSQL=PrepareSQL("SELECT idFile FROM file WHERE strFileName LIKE '%s'", strFileName.c_str());
    m_pDS->query(strSQL.c_str());

    if (m_pDS->num_rows() > 0)
      return m_pDS->fv("idFile").get_asInt();

  } catch (...) {
    CLog::Log(LOGERROR, "dbPFCCache: Failed: AddFile(%s)", strFileName.c_str());
    return -1;
  }

  int idPath = AddPath(strPath);
  if (idPath == -1) return -1;

  CDatabase::BeginTransaction();
  try
  {
    CStdString strSQL=PrepareSQL("INSERT INTO file(idPath, strFileName) VALUES('%i','%s')\n", idPath, strFileName.c_str());
    m_pDS->exec(strSQL.c_str());
    m_pDS->post();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "dbPFCCache: Failed adding file to cache: %s", strFullFilePath.c_str());
    RollbackTransaction();
    return -1;
  }
  CommitTransaction();
  return (int)m_pDS->lastinsertid();
}

int dbPFCCache::GetFilePath(const CStdString& strFileName) {
  if (NULL == m_pDB.get()) return false;
  if (NULL == m_pDS.get()) return false;

  try {
    CStdString strSQL=PrepareSQL("SELECT idPath FROM file WHERE strFileName LIKE '%s'", strFileName.c_str());
    m_pDS->query(strSQL.c_str());

    if (m_pDS->num_rows() > 0)
      return m_pDS->fv("idPath").get_asInt();

  } catch (...) {
    CLog::Log(LOGERROR, "dbPFCCache: Failed: GetFilePath(%s)", strFileName.c_str());
    return -1;
  }
  return -1;
}

int dbPFCCache::GetFilePath(int idFile) {
  if (NULL == m_pDB.get()) return false;
  if (NULL == m_pDS.get()) return false;

  try {
    CStdString strSQL=PrepareSQL("SELECT idPath FROM file WHERE idFile = %i", idFile);
    m_pDS->query(strSQL.c_str());

    if (m_pDS->num_rows() > 0)
      return m_pDS->fv("idPath").get_asInt();

  } catch (...) {
    CLog::Log(LOGERROR, "dbPFCCache: Failed: GetFilePath(%s)", idFile);
    return -1;
  }
  return -1;
}

//bool dbPFCCache::LogPlayedItem(CFileItem* pItem) {
//  try	{
//    if (NULL == m_pDB.get()) return false;
//    if (NULL == m_pDS.get()) return false;
//
//    CStdString strArtist = pItem->GetMusicInfoTag()->GetArtist();
//    CStdString strAlbum = pItem->GetMusicInfoTag()->GetAlbum();
//    CStdString strTitle = pItem->GetMusicInfoTag()->GetTitle();
//    CStdString strLabel = pItem->GetMusicInfoTag()->GetLabel();
//
//    if (pItem->IsAudio())
//    {
//      CStdString sql = PrepareSQL("INSERT INTO song(idSong, strArtist, strAlbum, strTitle, strLabel) VALUES(0, '%s', '%s', '%s', '%s')", strArtist.c_str(), strAlbum.c_str(), strTitle.c_str(), strLabel.c_str());
//      m_pDS->exec(sql.c_str());
//    }
//    else
//    if (pItem->IsVideo())
//    {
//      CStdString sql = PrepareSQL("INSERT INTO video(idVideo, strArtist, strAlbum, strTitle, strLabel) VALUES(0, '%s', '%s', '%s', '%s')", strArtist.c_str(), strAlbum.c_str(), strTitle.c_str(), strLabel.c_str());
//      m_pDS->exec(sql.c_str());
//    }
//
//
//    //sql = PrepareSQL("INSERT INTO coinslog(strWhen,coins) VALUES(datetime('now'),%i)", iAmount);
//    //m_pDS->exec(sql.c_str());
//
//    return true;
//  }
//  catch (...)	{
//    CLog::Log(LOGERROR, "%s failed on adding media stat", __FUNCTION__);
//  }
//  return false;
//}


