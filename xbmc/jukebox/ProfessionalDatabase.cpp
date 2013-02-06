#include "ProfessionalDatabase.h"
#include "utils/log.h"
#include "utils/StringUtils.h"
//#include "utils/AutoPtrHandle.h"
#include "dbwrappers/dataset.h"

using namespace std;
//using namespace AUTOPTR;
//using namespace dbiplus;
//using namespace XFILE;


CProfessionalDatabase::CProfessionalDatabase(): CDatabase() {
}

CProfessionalDatabase::~CProfessionalDatabase() {
}

bool CProfessionalDatabase::Open() {
  return CDatabase::Open();
}

bool CProfessionalDatabase::CommitTransaction() {
  return CDatabase::CommitTransaction();
}

bool CProfessionalDatabase::UpdateOldVersion( int version ) {
  return true;
}

void CProfessionalDatabase::CreateViews() {
  CLog::Log(LOGINFO, "No views avaiable in professional database...");
}


bool CProfessionalDatabase::CreateTables() {
  if (NULL == m_pDB.get()) return false;
  if (NULL == m_pDS.get()) return false;

  CDatabase::BeginTransaction();
  try	{
    CDatabase::CreateTables();

    CLog::Log(LOGINFO, "create professional table");
    m_pDS->exec("CREATE TABLE professional (id integer primary key, coins integer, prepaid integer, total double, cont integer)\n");

    //CLog::Log(LOGINFO, "create professional index");
    //m_pDS->exec("CREATE INDEX idxProfessional ON professional(id)");

    //CLog::Log(LOGINFO, "create coinslog table");
    //m_pDS->exec("CREATE TABLE coinslog (id integer primary key, strWhen text, coins integer)\n");

    //CLog::Log(LOGINFO, "create coinslog index");
    //m_pDS->exec("CREATE UNIQUE INDEX idxCoinslog ON coinslog(id)");

    m_pDS->exec("INSERT INTO professional (id, coins, prepaid, total, cont) VALUES(0,0,0,0,0)\n");
    m_pDS->post();
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

bool CProfessionalDatabase::AddCoin(int iAmount) {
  try	{
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;

    CStdString sql = PrepareSQL("UPDATE professional SET coins=coins + %i, cont=cont + %i WHERE id =0", iAmount);
    m_pDS->exec(sql.c_str());
    
    //sql = PrepareSQL("INSERT INTO coinslog(strWhen,coins) VALUES(datetime('now'),%i)", iAmount);
    //m_pDS->exec(sql.c_str());

    return true;
  }
  catch (...)	{
    CLog::Log(LOGERROR, "%s failed on adding %i coin(s)", __FUNCTION__, iAmount);
  }
  return false;
}

bool CProfessionalDatabase::RemoveCoin(int iAmount) {
  try	{
    if (NULL == m_pDB.get()) return false;
    //if (NULL == m_pDS.get()) return false;

    CStdString sql = PrepareSQL("UPDATE professional SET coins=coins - %i, cont=cont - %i WHERE id =0", iAmount);
    m_pDS->exec(sql.c_str());

    //sql = PrepareSQL("INSERT INTO coinslog(strWhen,coins) VALUES(datetime('now'),-%i)", iAmount);
    //m_pDS->exec(sql.c_str());

    return true;
  }
  catch (...)	{
    CLog::Log(LOGERROR, "%s failed on removing %i coin(s)", __FUNCTION__, iAmount);
  }
  return false;
}

int CProfessionalDatabase::GetCoins() {
  try {
    CStdString strSQL = PrepareSQL("select coins from professional where id =0");

    if (!m_pDS->query(strSQL.c_str()))
      return -1;

    if (m_pDS->num_rows() != 0)	{
      return m_pDS->fv("coins").get_asInt();
    }
  }
  catch (...) {
    CLog::Log(LOGERROR, "%s failed on reading database", __FUNCTION__);
    return -1;
  }
  //m_pDS->close();
  return -1;
}