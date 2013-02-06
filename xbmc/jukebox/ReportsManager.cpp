/*
 * ReportsManager.cpp
 *
 *  Created on: Oct 8, 2012
 *      Author: laureon
 */

#include "ReportsManager.h"
#include <time.h>

#include "utils/URIUtils.h"
#include "utils/log.h"
#include "filesystem/File.h"
#include "dialogs/GUIDialogOK.h"
#include "guilib/GUIWindowManager.h"

CReportManager::CReportManager() {
  m_strOperatorCode = "MGX";
  m_strMachineCode = "0000";
  //m_StatsDatabase.Open();
}

CReportManager::~CReportManager() {
  //m_StatsDatabase.Open();
}

bool CReportManager::LogPlayedItem(CFileItem* pItem) {
  return m_StatsDatabase.LogPlayedItem(pItem);
}


bool CReportManager::ExportReport(eREPORT eReportType, const CStdString& strPath, bool bRecoverLast) {
  CStdString strReport;

  switch (eReportType) {
    case REPORT_ABLF: {
      CStdString strFileName = URIUtils::AddFileToFolder(strPath, m_strOperatorCode + m_strMachineCode +"_musica.xml");
      strReport = m_StatsDatabase.GetABLFReport(bRecoverLast);
      CLog::Log(LOGDEBUG,"%s: Played Report: %s", __FUNCTION__, strReport.c_str());
      return GenerateReport(strReport, strFileName);
    }
    break;
    case REPORT_APROVA:
      CStdString strFileName = URIUtils::AddFileToFolder(strPath, m_strOperatorCode + m_strMachineCode +"_propaganda.xml");
      strReport = m_StatsDatabase.GetAdvertisingReport(bRecoverLast);
      CLog::Log(LOGDEBUG,"%s: Advert Report: %s", __FUNCTION__, strReport.c_str());
      return GenerateReport(strReport, strFileName);
    break;
  }

  return false;
}

CStdString CReportManager::GetDateTime() {
  time_t rawtime;
  struct tm * timeinfo;
  char buffer [80];

  time ( &rawtime );
  timeinfo = localtime( &rawtime );

  strftime(buffer,80, "%Y-%m-%d %H:%M:%S", timeinfo);
  return buffer;
}

bool CReportManager::HasBackups(eREPORT eReportType) {
  return false;
}

void CReportManager::SetOperatorCode(const CStdString& strCode) {
  m_strOperatorCode = strCode;
}

CStdString CReportManager::GetOperatorCode() {
  return m_strOperatorCode;
}

CStdString CReportManager::GetMachineCode() {
  return m_strMachineCode;
}

void CReportManager::SetMachineCode(const CStdString& strCode) {
  m_strMachineCode = strCode;
}

void CReportManager::ShowMessage(const CVariant& heading, const CVariant& line0, const CVariant& line1, const CVariant& line2) {
  CGUIDialogOK *dlgResult = (CGUIDialogOK *)g_windowManager.GetWindow(WINDOW_DIALOG_OK);
  if (!dlgResult) {
    CLog::Log(LOGERROR,"%s: ERROR CREATING DIALOG", __FUNCTION__);
    return;
  }

  dlgResult->ShowAndGetInput(heading,line0,line1,line2);
}

bool CReportManager::GenerateReport(const CStdString& strReport, const CStdString& strFilePath) {
  CStdString strCryptoReport;
  // Laureon: TODO: Grab hardlock key from g_HardLockManager (what should be a thread)
  m_CryptoManager.EncryptText("ff1cf3dc642f76e2", strReport, strCryptoReport);
  if (strCryptoReport.empty())
  {
    CLog::Log(LOGERROR,"%s: report was empty", __FUNCTION__);
    ShowMessage(70002,70010,70011,-1);
    return false;
  }

  bool bFileSaved = SaveTextFile(strCryptoReport, strFilePath);
  if (!bFileSaved) {
    ShowMessage(70002,70010,70011,-1);
    return false;
  }

  ShowMessage(70002,70008,-1,-1);
  return true;
}

bool CReportManager::SaveTextFile(const CStdString& strContent, const CStdString& strFilePath) {
  if (strContent.empty()) return false;
  if (strFilePath.empty()) return false;

  XFILE::CFile oFile;
  int iContentSize = strContent.size();

  if (!oFile.OpenForWrite(strFilePath.c_str(), true)) {
      return false;
  }

  if (oFile.Write(strContent.c_str(), iContentSize) != iContentSize) return false;

  oFile.Close();
  return true;
}
