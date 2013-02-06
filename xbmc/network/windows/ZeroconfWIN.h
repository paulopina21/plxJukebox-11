#pragma once


#include <memory>

#include "network/Zeroconf.h"
#include "threads/CriticalSection.h"
#include <dns_sd.h>

class CZeroconfWIN : public CZeroconf
{
public:
  CZeroconfWIN();
  ~CZeroconfWIN();
protected:
  //implement base CZeroConf interface
  bool doPublishService(const std::string& fcr_identifier,
                        const std::string& fcr_type,
                        const std::string& fcr_name,
                        unsigned int f_port,
                        std::map<std::string, std::string> txt);

  bool doRemoveService(const std::string& fcr_ident);

  virtual void doStop();

  bool IsZCdaemonRunning();

private:

  static void DNSSD_API registerCallback(DNSServiceRef sdref, const DNSServiceFlags flags, DNSServiceErrorType errorCode, const char *name, const char *regtype, const char *domain, void *context);


  //lock + data (accessed from runloop(main thread) + the rest)
  CCriticalSection m_data_guard;
  typedef std::map<std::string, DNSServiceRef> tServiceMap;
  tServiceMap m_services;
};
