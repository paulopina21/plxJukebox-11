

#pragma once
#include "DVDDemux.h"
#include "filesystem/HTSPSession.h"

class CDVDInputStreamHTSP;
typedef struct htsmsg htsmsg_t;

class CDVDDemuxHTSP : public CDVDDemux
{
public:
  CDVDDemuxHTSP();
  virtual ~CDVDDemuxHTSP();

  bool Open(CDVDInputStream* input);
  void Dispose();
  void Reset();
  void Flush();
  void Abort();
  void SetSpeed(int iSpeed){};

  std::string   GetFileName();

  DemuxPacket*  Read();

  bool          SeekTime(int time, bool backwords = false, double* startpts = NULL) { return false; }
  int           GetStreamLength()                                                   { return 0; }

  CDemuxStream* GetStream(int iStreamId);
  int           GetNrOfStreams();

protected:
  friend class CDemuxStreamVideoHTSP;

  void SubscriptionStart (htsmsg_t *m);
  void SubscriptionStop  (htsmsg_t *m);
  void SubscriptionStatus(htsmsg_t *m);

  htsmsg_t* ReadStream();
  bool      ReadStream(uint8_t* buf, int len);

  typedef std::vector<CDemuxStream*> TStreams;

  CDVDInputStream*     m_Input;
  TStreams             m_Streams;
  std::string          m_Status;
  int                  m_StatusCount;
  HTSP::SQueueStatus   m_QueueStatus;
};
