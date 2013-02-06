#pragma once


#include "FileItem.h"
#include "PlayerCoreFactory.h"

class CRegExp;
class TiXmlElement;

class CPlayerSelectionRule
{
public:
  CPlayerSelectionRule(TiXmlElement* rule);
  virtual ~CPlayerSelectionRule();

  //bool Matches(const CFileItem& item) const;
  //CStdString GetPlayerName() const;
  void GetPlayers(const CFileItem& item, VECPLAYERCORES &vecCores);

private:
  int GetTristate(const char* szValue) const;
  bool CompileRegExp(const CStdString& str, CRegExp& regExp) const;
  bool MatchesRegExp(const CStdString& str, CRegExp& regExp) const;
  void Initialize(TiXmlElement* pRule);
  PLAYERCOREID GetPlayerCore();

  CStdString m_name;

  int m_tAudio;
  int m_tVideo;
  int m_tInternetStream;

  int m_tDVD;
  int m_tDVDFile;
  int m_tDVDImage;

  CStdString m_protocols;
  CStdString m_fileTypes;
  CStdString m_mimeTypes;
  CStdString m_fileName;

  bool m_bStreamDetails;
  CStdString m_audioCodec;
  CStdString m_audioChannels;
  CStdString m_videoCodec;
  CStdString m_videoResolution;
  CStdString m_videoAspect;

  CStdString m_playerName;
  PLAYERCOREID m_playerCoreId;

  std::vector<CPlayerSelectionRule *> vecSubRules;
};
