#ifndef _PLXJUKEBOX_JUKEBOX_REPORTSMANAGER_H_
#define _PLXJUKEBOX_JUKEBOX_REPORTSMANAGER_H_

#pragma once

#include "StatsDatabase.h"
#include "CryptoManager.h"

//#include "utils/Stopwatch.h"

enum eREPORT {REPORT_ABLF, REPORT_APROVA};

class CReportManager {
private:
  CryptoManager m_CryptoManager;
	CStatsDatabase m_StatsDatabase;
	CStdString m_strOperatorCode;
	CStdString m_strMachineCode;

	CStdString GetDateTime();

	void ShowMessage(const CVariant &heading, const CVariant &line0, const CVariant &line1, const CVariant &line2);
	bool GenerateReport(const CStdString& strReport, const CStdString& strFilePath);
public:
	CReportManager();
	~CReportManager();

	bool LogPlayedItem(CFileItem* pItem);
  bool ExportReport(eREPORT eReportType, const CStdString& strPath, bool bRecoverLast = false);
	bool HasBackups(eREPORT eReportType);

	CStdString GetOperatorCode();
	CStdString GetMachineCode();

	void SetOperatorCode(const CStdString& strCode);
  void SetMachineCode(const CStdString& strCode);
  bool SaveTextFile(const CStdString& strContent, const CStdString& strFilePath);
};

//extern CReportManager g_jukeboxManager;
#endif


//AutoSeededRandomPool rnd;
//
//// Generate a random key
//SecByteBlock key(AES::DEFAULT_KEYLENGTH);
//rnd.GenerateBlock( key, key.size() );
//
//// Generate a random IV
//byte iv[AES::BLOCKSIZE];
//rnd.GenerateBlock(iv, AES::BLOCKSIZE);
//
//char plainText[] = "Hello! How are you.";
//int messageLen = (int)strlen(plainText) + 1;
//
////////////////////////////////////////////////////////////////////////////
//// Encrypt
//
//CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), iv);
//cfbEncryption.ProcessData((byte*)plainText, (byte*)plainText, messageLen);
//
//
//------------------------------------------------------------------------------------------------------------------


//ff1cf3dc642f76e2
