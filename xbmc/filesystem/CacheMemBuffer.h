

#ifndef CACHEMEMBUFFER_H
#define CACHEMEMBUFFER_H

#include "CacheStrategy.h"
#include "threads/CriticalSection.h"
#include "threads/Event.h"
#include "utils/RingBuffer.h"

/**
  @author Team XBMC
*/
namespace XFILE {

class CacheMemBuffer : public CCacheStrategy
{
public:
    CacheMemBuffer();
    virtual ~CacheMemBuffer();

    virtual int Open() ;
    virtual void Close();

    virtual int WriteToCache(const char *pBuffer, size_t iSize) ;
    virtual int ReadFromCache(char *pBuffer, size_t iMaxSize) ;
    virtual int64_t WaitForData(unsigned int iMinAvail, unsigned int iMillis) ;

    virtual int64_t Seek(int64_t iFilePosition) ;
    virtual void Reset(int64_t iSourcePosition) ;

protected:
    int64_t m_nStartPosition;
    CRingBuffer m_buffer;
    CRingBuffer m_HistoryBuffer;
    CRingBuffer m_forwardBuffer; // for seek cases, to store data already read
    CCriticalSection m_sync;
    CEvent m_written;
};

} // namespace XFILE
#endif
