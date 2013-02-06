

#ifndef LIBREFM_SCROBBLER_H__
#define LIBREFM_SCROBBLER_H__

#include "scrobbler.h"

#define LIBREFM_SCROBBLER_HANDSHAKE_URL  "turtle.libre.fm"
#define LIBREFM_SCROBBLER_LOG_PREFIX     "CLibrefmScrobbler"

class CLibrefmScrobbler : public CScrobbler
{
private:
  static long m_instanceLock;
  static CLibrefmScrobbler *m_pInstance;
  virtual void LoadCredentials();
  virtual void NotifyUser(int error);
  virtual bool CanScrobble();
  virtual CStdString GetJournalFileName();
public:
  CLibrefmScrobbler();
  virtual ~CLibrefmScrobbler();
  static CLibrefmScrobbler *GetInstance();
  static void RemoveInstance();
};

#endif // LIBREFM_SCROBBLER_H__
