#pragma once



#include "threads/Thread.h"
#include "IProgressCallback.h"
#include "threads/CriticalSection.h"

#include <vector>
#include "boost/shared_ptr.hpp"

class CFileItem; typedef boost::shared_ptr<CFileItem> CFileItemPtr;
class CFileItemList;

class IBackgroundLoaderObserver
{
public:
  virtual ~IBackgroundLoaderObserver() {}
  virtual void OnItemLoaded(CFileItem* pItem) = 0;
};

class CBackgroundInfoLoader : public IRunnable
{
public:
  CBackgroundInfoLoader(int nThreads=-1);
  virtual ~CBackgroundInfoLoader();

  void Load(CFileItemList& items);
  bool IsLoading();
  virtual void Run();
  void SetObserver(IBackgroundLoaderObserver* pObserver);
  void SetProgressCallback(IProgressCallback* pCallback);
  virtual bool LoadItem(CFileItem* pItem) { return false; };

  void StopThread(); // will actually stop all worker threads.
  void StopAsync();  // will ask loader to stop as soon as possible, but not block

  void SetNumOfWorkers(int nThreads); // -1 means auto compute num of required threads

protected:
  virtual void OnLoaderStart() {};
  virtual void OnLoaderFinish() {};

  CFileItemList *m_pVecItems;
  std::vector<CFileItemPtr> m_vecItems; // FileItemList would delete the items and we only want to keep a reference.
  CCriticalSection m_lock;

  bool m_bStartCalled;
  volatile bool m_bStop;
  int  m_nRequestedThreads;
  int  m_nActiveThreads;

  IBackgroundLoaderObserver* m_pObserver;
  IProgressCallback* m_pProgressCallback;

  std::vector<CThread *> m_workers;
};

