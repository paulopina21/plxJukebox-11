

#ifndef LASTFM_SCROBBLER_H__
#define LASTFM_SCROBBLER_H__

#include "scrobbler.h"

#define LASTFM_SCROBBLER_HANDSHAKE_URL  "post.audioscrobbler.com"
#define LASTFM_SCROBBLER_LOG_PREFIX     "CLastfmScrobbler"

class CLastfmScrobbler : public CScrobbler
{
private:
  static long m_instanceLock;
  static CLastfmScrobbler *m_pInstance;
  virtual void LoadCredentials();
  virtual void NotifyUser(int error);
  virtual bool CanScrobble();
  virtual CStdString GetJournalFileName();
public:
//  CLastfmScrobbler() : CScrobbler(LASTFM_SCROBBLER_HANDSHAKE_URL, LASTFM_SCROBBLER_LOG_PREFIX) {}
//  virtual ~CLastfmScrobbler() {}
  CLastfmScrobbler();
  virtual ~CLastfmScrobbler();
  static CLastfmScrobbler *GetInstance();
  static void RemoveInstance();
};

#endif // LASTFM_SCROBBLER_H__
