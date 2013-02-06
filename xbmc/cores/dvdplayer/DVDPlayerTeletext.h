#pragma once



#include "threads/Thread.h"
#include "DVDMessageQueue.h"
#include "video/TeletextDefines.h"

class CDVDStreamInfo;

class CDVDTeletextData : public CThread
{
public:
  CDVDTeletextData();
  ~CDVDTeletextData();

  bool CheckStream(CDVDStreamInfo &hints);
  bool OpenStream(CDVDStreamInfo &hints);
  void CloseStream(bool bWaitForBuffers);
  void Flush();

  // waits until all available data has been rendered
  void WaitForBuffers() { m_messageQueue.WaitUntilEmpty(); }
  bool AcceptsData() { return !m_messageQueue.IsFull(); }
  void SendMessage(CDVDMsg* pMsg) { if(m_messageQueue.IsInited()) m_messageQueue.Put(pMsg); }

  TextCacheStruct_t* GetTeletextCache() { return &m_TXTCache; }
  void LoadPage(int p, int sp, unsigned char* buffer);

  CDVDMessageQueue m_messageQueue;

protected:
  virtual void OnExit();
  virtual void Process();

private:
  void ResetTeletextCache();
  void Decode_p2829(unsigned char *vtxt_row, TextExtData_t **ptExtData);
  void SavePage(int p, int sp, unsigned char* buffer);
  void ErasePage(int magazine);
  void AllocateCache(int magazine);

  int m_speed;
  TextCacheStruct_t  m_TXTCache;
  CCriticalSection m_critSection;
};

