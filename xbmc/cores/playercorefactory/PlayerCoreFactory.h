#pragma once



#include "../IPlayer.h"

/*----------------------------------------------------------------------
|   forward references
+---------------------------------------------------------------------*/
class TiXmlElement;
class CPlayerCoreConfig;
class CPlayerSelectionRule;

// do not remove mplayer - will break scripts
enum EPLAYERCORES
{
  EPC_NONE,
  EPC_DVDPLAYER,
  EPC_MPLAYER,
  EPC_PAPLAYER,
  EPC_EXTPLAYER
};

typedef unsigned int PLAYERCOREID;
typedef std::vector<PLAYERCOREID> VECPLAYERCORES;
const PLAYERCOREID PCID_NONE = 0;
const PLAYERCOREID PCID_DVDPLAYER = 1;
const PLAYERCOREID PCID_MPLAYER = 2;
const PLAYERCOREID PCID_PAPLAYER = 3;

class CPlayerCoreFactory
{
public:
  CPlayerCoreFactory();
  virtual ~CPlayerCoreFactory();

  IPlayer* CreatePlayer(const CStdString& strCore, IPlayerCallback& callback) const;

  static PLAYERCOREID GetPlayerCore(const CStdString& strCoreName);
  static CPlayerCoreConfig* GetPlayerConfig(const CStdString& strCoreName);
  static CStdString GetPlayerName(const PLAYERCOREID eCore);

  static IPlayer* CreatePlayer(const PLAYERCOREID eCore, IPlayerCallback& callback);
  static void GetPlayers( const CFileItem& item, VECPLAYERCORES &vecCores);   //Players supporting the specified file
  static void GetPlayers( VECPLAYERCORES &vecCores, bool audio, bool video ); //All audio players and/or video players
  static void GetPlayers( VECPLAYERCORES &vecCores );                         //All players

  static PLAYERCOREID GetDefaultPlayer( const CFileItem& item );

  static PLAYERCOREID SelectPlayerDialog(VECPLAYERCORES &vecCores, float posX = 0, float posY = 0);
  static PLAYERCOREID SelectPlayerDialog(float posX, float posY);

  static bool LoadConfiguration(TiXmlElement* pConfig, bool clear);

private:
  static std::vector<CPlayerCoreConfig *> s_vecCoreConfigs;
  static std::vector<CPlayerSelectionRule *> s_vecCoreSelectionRules;
};
