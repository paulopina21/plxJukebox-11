#pragma once



#include <queue>
#include "threads/Thread.h"
#include "threads/CriticalSection.h"
#include "StdString.h"

struct TICKET
{
  TICKET(WORD aQueueId, DWORD aItemId)
  {
    wQueueId = aQueueId;
    dwItemId = aItemId;
  };

  WORD wQueueId;
  DWORD dwItemId;
};

class IDownloadQueueObserver
{
public:
  enum Result {Succeeded, Failed};
  virtual ~IDownloadQueueObserver() {};
  virtual void OnContentComplete(TICKET aTicket, CStdString& aContentString, Result aResult){};
  virtual void OnFileComplete(TICKET aTicket, CStdString& aFilePath, INT aByteRxCount, Result aResult){};
};


class CDownloadQueue: CThread
{
public:
  CDownloadQueue();
  virtual ~CDownloadQueue(void);

  TICKET RequestContent(const CStdString& aUrl, IDownloadQueueObserver* aObserver);
  TICKET RequestFile(const CStdString& aUrl, IDownloadQueueObserver* aObserver);
  TICKET RequestFile(const CStdString& aUrl, const CStdString& aFilePath, IDownloadQueueObserver* aObserver);
  void CancelRequests(IDownloadQueueObserver* aObserver);

  VOID Flush();
  INT Size();

protected:

  void OnStartup();
  void Process();

  struct Command
  {
    TICKET ticket;
    CStdString location;
    CStdString content;
    IDownloadQueueObserver* observer;
  };

  typedef std::queue<Command> COMMANDQUEUE;
  COMMANDQUEUE m_queue;
  CCriticalSection m_critical;

  WORD m_wQueueId;
  DWORD m_dwNextItemId;

  static WORD m_wNextQueueId;
};
