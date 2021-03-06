#pragma once


#include <memory>
#include <CoreFoundation/CoreFoundation.h>
#if !defined(__arm__)
#include <Carbon/Carbon.h>
#include <CoreServices/CoreServices.h>
#else
#include <CFNetwork/CFNetServices.h>
#endif

#include "network/Zeroconf.h"
#include "threads/CriticalSection.h"

class CZeroconfOSX : public CZeroconf
{
public:
  CZeroconfOSX();
  ~CZeroconfOSX();
protected:
  //implement base CZeroConf interface
  bool doPublishService(const std::string& fcr_identifier,
                        const std::string& fcr_type,
                        const std::string& fcr_name,
                        unsigned int f_port,
                        std::map<std::string, std::string> txt);

  bool doRemoveService(const std::string& fcr_ident);

  virtual void doStop();

private:
  static void registerCallback(CFNetServiceRef theService, CFStreamError* error, void* info);
  void cancelRegistration(CFNetServiceRef theService);

  //CF runloop ref; we're using main-threads runloop
  CFRunLoopRef m_runloop;

  //lock + data (accessed from runloop(main thread) + the rest)
  CCriticalSection m_data_guard;
  typedef std::map<std::string, CFNetServiceRef> tServiceMap;
  tServiceMap m_services;
};
