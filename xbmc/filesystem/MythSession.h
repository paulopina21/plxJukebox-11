#pragma once


#include "threads/CriticalSection.h"
#include "threads/Thread.h"

typedef struct cmyth_ringbuf   *cmyth_ringbuf_t;
typedef struct cmyth_conn      *cmyth_conn_t;
typedef struct cmyth_recorder  *cmyth_recorder_t;
typedef struct cmyth_proginfo  *cmyth_proginfo_t;
typedef struct cmyth_proglist  *cmyth_proglist_t;
typedef struct cmyth_file      *cmyth_file_t;
typedef struct cmyth_database  *cmyth_database_t;
typedef struct cmyth_timestamp *cmyth_timestamp_t;

class DllLibCMyth;
class CDateTime;
class CFileItem;
class CURL;

namespace XFILE
{

class CMythSession
  : private CThread
{
public:
  static CMythSession*  AquireSession(const CURL& url);
  static void           ReleaseSession(CMythSession*);
  static void           CheckIdle();
  static void           LogCMyth(int level, char *msg);

  class IEventListener
  {
  public:
    virtual ~IEventListener() {};
    virtual void OnEvent(int event, const std::string& data)=0;
  };

  bool             SetListener(IEventListener *listener);
  cmyth_conn_t     GetControl();
  cmyth_database_t GetDatabase();
  DllLibCMyth*     GetLibrary();
  cmyth_proglist_t GetAllRecordedPrograms();
  void             ResetAllRecordedPrograms();

  void             SetFileItemMetaData(CFileItem &item, cmyth_proginfo_t program);

  CDateTime        GetValue(cmyth_timestamp_t t);
  CStdString       GetValue(char* str);

private:
  CMythSession(const CURL& url);
  ~CMythSession();

  virtual void Process();

  bool             CanSupport(const CURL& url);
  void             Disconnect();

  void             SetSeasonAndEpisode(const cmyth_proginfo_t &program, int *season, int *epsiode);

  IEventListener*  m_listener;
  cmyth_conn_t     m_control;
  cmyth_conn_t     m_event;
  cmyth_database_t m_database;
  CStdString       m_hostname;
  CStdString       m_username;
  CStdString       m_password;
  int              m_port;
  DllLibCMyth*     m_dll;
  CCriticalSection m_section;
  unsigned int     m_timestamp;
  cmyth_proglist_t m_all_recorded; // Cache of all_recorded programs.

  static CCriticalSection            m_section_session;
  static std::vector<CMythSession*>  m_sessions;
};

}
