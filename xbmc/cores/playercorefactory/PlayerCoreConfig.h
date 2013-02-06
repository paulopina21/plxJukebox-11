#pragma once


#include "tinyXML/tinyxml.h"
#include "cores/IPlayer.h"
#include "PlayerCoreFactory.h"
#include "cores/dvdplayer/DVDPlayer.h"
#include "cores/paplayer/PAPlayer.h"
#include "cores/ExternalPlayer/ExternalPlayer.h"
#include "utils/log.h"

class CPlayerCoreConfig
{
friend class CPlayerCoreFactory;

public:
  CPlayerCoreConfig(CStdString name, const EPLAYERCORES eCore, const TiXmlElement* pConfig)
  {
    m_name = name;
    m_eCore = eCore;
    m_bPlaysAudio = false;
    m_bPlaysVideo = false;

    if (pConfig)
    {
      m_config = (TiXmlElement*)pConfig->Clone();
      const char *szAudio = pConfig->Attribute("audio");
      const char *szVideo = pConfig->Attribute("video");
      m_bPlaysAudio = szAudio && stricmp(szAudio, "true") == 0;
      m_bPlaysVideo = szVideo && stricmp(szVideo, "true") == 0;
    }
    else
    {
      m_config = NULL;
    }
    CLog::Log(LOGDEBUG, "CPlayerCoreConfig::<ctor>: created player %s for core %d", m_name.c_str(), m_eCore);
  }

  virtual ~CPlayerCoreConfig()
  {
    SAFE_DELETE(m_config);
  }

  const CStdString& GetName() const
  {
    return m_name;
  }

  IPlayer* CreatePlayer(IPlayerCallback& callback) const
  {
    IPlayer* pPlayer;
    switch(m_eCore)
    {
      case EPC_MPLAYER:
      case EPC_DVDPLAYER: pPlayer = new CDVDPlayer(callback); break;
      case EPC_PAPLAYER: pPlayer = new PAPlayer(callback); break;
      case EPC_EXTPLAYER: pPlayer = new CExternalPlayer(callback); break;
      default: return NULL;
    }

    if (pPlayer->Initialize(m_config))
    {
      return pPlayer;
    }
    else
    {
      SAFE_DELETE(pPlayer);
      return NULL;
    }
  }

private:
  CStdString m_name;
  bool m_bPlaysAudio;
  bool m_bPlaysVideo;
  EPLAYERCORES m_eCore;
  TiXmlElement* m_config;
};
