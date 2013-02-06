#pragma once

#include "ProfessionalDatabase.h"
#include "StatsDatabase.h"

#include "utils/Stopwatch.h"

#define COOLDOWNTIME 180.0f
#define COOLDOWNMAXSONGS 5

struct sPrize {
	CStdString m_description;
	int m_frequence;
	int m_counter;
};

class CBreaksManager {
private:
	CProfessionalDatabase m_db;
	CStatsDatabase m_StatsDatabase;
	CStopWatch	  m_breaksTimer;

	unsigned int m_coolDownCounter;

	bool m_started;

	int64_t m_coins;
	double m_totalMoney;

	// Machine builder info
	CStdString m_owner;
	CStdString m_contactName;
	CStdString m_contactPhone;
	CStdString m_serialNumber;

	void CoolDownReset();

public:
	CJukeboxManager();
	~CJukeboxManager();
	
	bool Start();
	
	bool InCoolDown();
	void AddCoolDownCount();
	CStdString GetCoolDownTime();

	int64_t InsertCredits(int64_t Amount = 1);
	int64_t RemoveCredits(int64_t Amount = 1);
	int64_t GetCredits();
	void RemoveLastSong();

	bool HasCredits();

  bool LogPlayedItem(CFileItem* pItem);
};

extern CJukeboxManager g_jukeboxManager;
