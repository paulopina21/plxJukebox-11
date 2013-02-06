  #ifndef __EVENT_SERVER_H__
#define __EVENT_SERVER_H__



#include "threads/Thread.h"
#include "Socket.h"
#include "EventClient.h"
#include "threads/CriticalSection.h"
#include "threads/SingleLock.h"

#include <map>
#include <queue>
#include <vector>

namespace EVENTSERVER
{

  /**********************************************************************/
  /* UDP Event Server Class                                             */
  /**********************************************************************/
  class CEventServer : private CThread
  {
  public:
    static void RemoveInstance();
    static CEventServer* GetInstance();
    virtual ~CEventServer() {}

    // IRunnable entry point for thread
    virtual void  Process();

    bool Running()
    {
      return m_bRunning;
    }

    void RefreshSettings()
    {
      CSingleLock lock(m_critSection);
      m_bRefreshSettings = true;
    }

    // start / stop server
    void StartServer();
    void StopServer(bool bWait);

    // get events
    unsigned short GetButtonCode(std::string& strMapName, bool& isAxis, float& amount);
    bool ExecuteNextAction();
    bool GetMousePos(float &x, float &y);
    int GetNumberOfClients();

  protected:
    CEventServer();
    void Cleanup();
    void Run();
    void ProcessPacket(SOCKETS::CAddress& addr, int packetSize);
    void ProcessEvents();
    void RefreshClients();

    std::map<unsigned long, EVENTCLIENT::CEventClient*>  m_clients;
    static CEventServer* m_pInstance;
    SOCKETS::CUDPSocket* m_pSocket;
    int              m_iPort;
    int              m_iListenTimeout;
    int              m_iMaxClients;
    unsigned char*   m_pPacketBuffer;
    bool             m_bRunning;
    CCriticalSection m_critSection;
    bool             m_bRefreshSettings;
  };

}

#endif // __EVENT_SERVER_H__
