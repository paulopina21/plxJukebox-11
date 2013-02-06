#pragma once



#include "utils/StdString.h"
#include "threads/Thread.h"
#include "threads/CriticalSection.h"
#include <sys/socket.h>
#include <netinet/in.h>

class CUdpClient : CThread
{
public:
  CUdpClient();
  virtual ~CUdpClient(void);

protected:

  bool Create();
  void Destroy();

  void OnStartup();
  void Process();

  bool Broadcast(int aPort, CStdString& aMessage);
  bool Send(CStdString aIpAddress, int aPort, CStdString& aMessage);
  bool Send(SOCKADDR_IN aAddress, CStdString& aMessage);
  bool Send(SOCKADDR_IN aAddress, LPBYTE pMessage, DWORD dwSize);

  virtual void OnMessage(SOCKADDR_IN& aRemoteAddress, CStdString& aMessage, LPBYTE pMessage, DWORD dwMessageLength){};

protected:

  struct UdpCommand
  {
    SOCKADDR_IN address;
    CStdString message;
    LPBYTE binary;
    DWORD binarySize;
  };

  bool DispatchNextCommand();

  SOCKET client_socket;

  std::vector<UdpCommand> commands;
  typedef std::vector<UdpCommand> ::iterator COMMANDITERATOR;

  CCriticalSection critical_section;
};
