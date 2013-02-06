#ifndef NETWORK_LINUX_H_
#define NETWORK_LINUX_H_



#include <vector>
#include "utils/StdString.h"
#include "network/Network.h"
#include "Iphlpapi.h"
#include "utils/stopwatch.h"
#include "threads/CriticalSection.h"

class CNetworkWin32;

class CNetworkInterfaceWin32 : public CNetworkInterface
{
public:
   CNetworkInterfaceWin32(CNetworkWin32* network, IP_ADAPTER_INFO adapter);
   ~CNetworkInterfaceWin32(void);

   virtual CStdString& GetName(void);

   virtual bool IsEnabled(void);
   virtual bool IsConnected(void);
   virtual bool IsWireless(void);

   virtual CStdString GetMacAddress(void);

   virtual CStdString GetCurrentIPAddress();
   virtual CStdString GetCurrentNetmask();
   virtual CStdString GetCurrentDefaultGateway(void);
   virtual CStdString GetCurrentWirelessEssId(void);

   virtual void GetSettings(NetworkAssignment& assignment, CStdString& ipAddress, CStdString& networkMask, CStdString& defaultGateway, CStdString& essId, CStdString& key, EncMode& encryptionMode);
   virtual void SetSettings(NetworkAssignment& assignment, CStdString& ipAddress, CStdString& networkMask, CStdString& defaultGateway, CStdString& essId, CStdString& key, EncMode& encryptionMode);

   // Returns the list of access points in the area
   virtual std::vector<NetworkAccessPoint> GetAccessPoints(void);

private:
   void WriteSettings(FILE* fw, NetworkAssignment assignment, CStdString& ipAddress, CStdString& networkMask, CStdString& defaultGateway, CStdString& essId, CStdString& key, EncMode& encryptionMode);
   IP_ADAPTER_INFO m_adapter;
   CNetworkWin32* m_network;
   CStdString m_adaptername;
};

class CNetworkWin32 : public CNetwork
{
public:
   CNetworkWin32(void);
   virtual ~CNetworkWin32(void);

   // Return the list of interfaces
   virtual std::vector<CNetworkInterface*>& GetInterfaceList(void);

   // Get/set the nameserver(s)
   virtual std::vector<CStdString> GetNameServers(void);
   virtual void SetNameServers(std::vector<CStdString> nameServers);

   friend class CNetworkInterfaceWin32;

private:
   int GetSocket() { return m_sock; }
   void queryInterfaceList();
   void CleanInterfaceList();
   std::vector<CNetworkInterface*> m_interfaces;
   int m_sock;
   CStopWatch m_netrefreshTimer;
   CCriticalSection m_critSection;
};

#endif
