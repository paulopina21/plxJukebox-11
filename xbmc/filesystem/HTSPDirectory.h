
#pragma once
#include "IDirectory.h"
#include "threads/Thread.h"
#include "threads/CriticalSection.h"
#include "threads/Event.h"
#include "URL.h"
#include "HTSPSession.h"
#include "boost/shared_ptr.hpp"

class CFileItem; typedef boost::shared_ptr<CFileItem> CFileItemPtr;

namespace HTSP
{
  class CHTSPDirectorySession
      : public CThread
  {
    public:
      bool                    GetEvent(SEvent& event, uint32_t id);
      SChannels               GetChannels();
      SChannels               GetChannels(int tag);
      SChannels               GetChannels(STag &tag);
      STags                   GetTags();
      htsmsg_t*               ReadResult(htsmsg_t* m);


      static CHTSPDirectorySession* Acquire(const CURL& url);
      static void                   Release(CHTSPDirectorySession* &session);
      static void                   CheckIdle(DWORD idle = 60000);

    protected:
       CHTSPDirectorySession();
      ~CHTSPDirectorySession();

      bool   Open(const CURL& url);
      void   Close();

    private:
      virtual void Process();
      CHTSPSession            m_session;
      SChannels               m_channels;
      STags                   m_tags;
      SEvents                 m_events;
      CCriticalSection        m_section;
      CEvent                  m_started;

      struct SMessage
      {
        CEvent   * event;
        htsmsg_t * msg;
      };
      typedef std::map<int, SMessage> SMessages;

      SMessages m_queue;
  };
}

namespace XFILE
{

  class CHTSPDirectory : public IDirectory
  {
    public:
      CHTSPDirectory(void);
      virtual ~CHTSPDirectory(void);
      virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
      virtual DIR_CACHE_TYPE GetCacheType(const CStdString& strPath) const { return DIR_CACHE_ONCE; };
    private:
      bool GetChannels(const CURL& base, CFileItemList &items);
      bool GetChannels(const CURL& base, CFileItemList &items, HTSP::SChannels channels, int tag);
      bool GetTag     (const CURL& base, CFileItemList &items);

      HTSP::CHTSPDirectorySession* m_session;
  };
}

