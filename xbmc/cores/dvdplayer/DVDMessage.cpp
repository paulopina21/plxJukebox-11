

#include "threads/SystemClock.h"
#include "DVDMessage.h"
#include "DVDDemuxers/DVDDemuxUtils.h"
#include "DVDStreamInfo.h"
#include "utils/TimeUtils.h"


/**
 * CDVDMsgGeneralSynchronize --- GENERAL_SYNCRONIZR
 */
CDVDMsgGeneralSynchronize::CDVDMsgGeneralSynchronize(DWORD timeout, DWORD sources) : CDVDMsg(GENERAL_SYNCHRONIZE)
{
  if( sources )
    m_sources = sources;
  else
    m_sources = SYNCSOURCE_ALL;

  m_objects = 0;
  m_timeout = timeout;
}

void CDVDMsgGeneralSynchronize::Wait(volatile bool *abort, DWORD source)
{
  /* if we are not requested to wait on this object just return, reference count will be decremented */
  if (source && !(m_sources & source)) return;

  AtomicIncrement(&m_objects);

  XbmcThreads::EndTime timeout(m_timeout);

  if (abort)
    while( m_objects < GetNrOfReferences() && !timeout.IsTimePast() && !(*abort)) Sleep(1);
  else
    while( m_objects < GetNrOfReferences() && !timeout.IsTimePast() ) Sleep(1);
}

/**
 * CDVDMsgDemuxerPacket --- DEMUXER_PACKET
 */
CDVDMsgDemuxerPacket::CDVDMsgDemuxerPacket(DemuxPacket* packet, bool drop) : CDVDMsg(DEMUXER_PACKET)
{
  m_packet = packet;
  m_drop   = drop;
}

CDVDMsgDemuxerPacket::~CDVDMsgDemuxerPacket()
{
  if (m_packet)
    CDVDDemuxUtils::FreeDemuxPacket(m_packet);
}
