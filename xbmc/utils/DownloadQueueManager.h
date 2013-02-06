#pragma once



#include "DownloadQueue.h"

#define MAX_DOWNLOAD_QUEUES  3

class CDownloadQueueManager
{
public:
  CDownloadQueueManager();
  virtual ~CDownloadQueueManager(void);

  VOID Initialize();
  TICKET RequestContent(const CStdString& aUrl, IDownloadQueueObserver* aObserver);
  TICKET RequestFile(const CStdString& aUrl, IDownloadQueueObserver* aObserver);
  TICKET RequestFile(const CStdString& aUrl, const CStdString& aFilePath, IDownloadQueueObserver* aObserver);
  void CancelRequests(IDownloadQueueObserver *aObserver);

protected:

  CDownloadQueue* GetNextDownloadQueue();

  typedef std::vector<CDownloadQueue*> QUEUEPOOL;
  QUEUEPOOL m_queues;

  CCriticalSection m_critical;
};

// Single global instance of class is in cpp file
extern CDownloadQueueManager g_DownloadManager;
