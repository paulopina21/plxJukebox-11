

#ifndef CACHECIRCULAR_H
#define CACHECIRCULAR_H

#include "CacheStrategy.h"
#include "threads/CriticalSection.h"
#include "threads/Event.h"

namespace XFILE {

class CCacheCircular : public CCacheStrategy
{
public:
    CCacheCircular(size_t front, size_t back);
    virtual ~CCacheCircular();

    virtual int Open() ;
    virtual void Close();

    virtual int WriteToCache(const char *buf, size_t len) ;
    virtual int ReadFromCache(char *buf, size_t len) ;
    virtual int64_t WaitForData(unsigned int minimum, unsigned int iMillis) ;

    virtual int64_t Seek(int64_t pos) ;
    virtual void Reset(int64_t pos) ;

protected:
    uint64_t          m_beg;       /**< index in file (not buffer) of beginning of valid data */
    uint64_t          m_end;       /**< index in file (not buffer) of end of valid data */
    uint64_t          m_cur;       /**< current reading index in file */
    uint8_t          *m_buf;       /**< buffer holding data */
    size_t            m_size;      /**< size of data buffer used (m_buf) */
    size_t            m_size_back; /**< guaranteed size of back buffer (actual size can be smaller, or larger if front buffer doesn't need it) */
    CCriticalSection  m_sync;
    CEvent            m_written;
#ifdef _WIN32
    HANDLE            m_handle;
#endif
};

} // namespace XFILE
#endif
