#pragma once

#include "ProfessionalDatabase.h"
#include "ReportsManager.h"

//#include "utils/Stopwatch.h"

#include "CoinsManager.h"
#include "PartyModeManager.h"
#include "RandomManager.h"

#define COOLDOWNTIME 180.0f
#define COOLDOWNMAXSONGS 5

struct sPrize {
	CStdString m_description;
	int m_frequence;
	int m_counter;
};

enum EJukeboxMode {
  EJUKEBOXMODE_DEFAULT = 0,
  EJUKEBOXMODE_PARTY = 1,
  EJUKEBOXMODE_PASSIVE = 2
};

class CJukeboxManager {
private:
  RandomManager m_randomManager;
  CoinsManager m_coinsManager;
  plxJukebox::PartyModeManager m_partyModeManager;

	CProfessionalDatabase m_db;
	CReportManager m_ReportsManager;

//	CStopWatch	  m_coolDownTimer;
//	unsigned int m_coolDownCounter;

	bool m_started;

//	int64_t m_coins;
//	double m_totalMoney;

	// Machine builder info
	CStdString m_owner;
	CStdString m_contactName;
	CStdString m_contactPhone;
	CStdString m_serialNumber;

	void CoolDownReset();

public:
	CJukeboxManager();
	~CJukeboxManager();
	IModeManager& GetModeManager();
	
	CoinsManager& GetCoinsManager();

	RandomManager& GetRandomManager();

	CReportManager& GetReportsManager();

	// STATS
  bool ExportReport(eREPORT eReportType, const CStdString& strPath, bool bRecoverLast = false);


	bool Start();
	
//	bool InCoolDown();
//	void AddCoolDownCount();
//	CStdString GetCoolDownTime();

//	int64_t InsertCredits(int64_t Amount = 1);
//	int64_t RemoveCredits(int64_t Amount = 1);
//	int64_t GetCredits();
//  bool HasCredits();
//	void RemoveLastSong();


//  bool LogPlayedItem(CFileItem* pItem);
};

extern CJukeboxManager g_jukeboxManager;
