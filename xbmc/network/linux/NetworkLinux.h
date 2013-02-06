#ifndef NETWORK_LINUX_H_
#define NETWORK_LINUX_H_



#include <vector>
#include "utils/StdString.h"
#include "network/Network.h"

class CNetworkLinux;

class CNetworkInterfaceLinux : public CNetworkInterface
{
public:
   CNetworkInterfaceLinux(CNetworkLinux* network, CStdString interfaceName, CStdString interfaceMacAdr);
   ~CNetworkInterfaceLinux(void);

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
   CStdString     m_interfaceName;
   CStdString     m_interfaceMacAdr;
   CNetworkLinux* m_network;
};

class CNetworkLinux : public CNetwork
{
public:
   CNetworkLinux(void);
   virtual ~CNetworkLinux(void);

   // Return the list of interfaces
   virtual std::vector<CNetworkInterface*>& GetInterfaceList(void);
#if defined(__APPLE__) && defined(__arm__)
   // on iOS, overwrite the GetFirstConnectedInterface and requery
   // the interface list if no connected device is found
   // this fixes a bug when no network is available after first start of xbmc after reboot
   virtual CNetworkInterface* GetFirstConnectedInterface(void);        
#endif
    
   // Get/set the nameserver(s)
   virtual std::vector<CStdString> GetNameServers(void);
   virtual void SetNameServers(std::vector<CStdString> nameServers);

   friend class CNetworkInterfaceLinux;

private:
   int GetSocket() { return m_sock; }
   CStdString GetMacAddress(CStdString interfaceName);
   void queryInterfaceList();
   std::vector<CNetworkInterface*> m_interfaces;
   int m_sock;
};

#endif

