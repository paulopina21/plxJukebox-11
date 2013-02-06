#pragma once


#include "IDirectory.h"
#include "MythSession.h"
#include "XBDateTime.h"

namespace XFILE
{

enum FilterType
{
  MOVIES,
  TV_SHOWS,
  ALL
};

class CMythDirectory
  : public IDirectory
{
public:
  CMythDirectory();
  virtual ~CMythDirectory();

  virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
  virtual bool Exists(const char* strPath);
  virtual bool IsAllowed(const CStdString &strFile) const { return true; };
  virtual DIR_CACHE_TYPE GetCacheType(const CStdString& strPath) const;

  static bool SupportsFileOperations(const CStdString& strPath);
  static bool IsLiveTV(const CStdString& strPath);

private:
  void Release();
  bool GetGuide(const CStdString& base, CFileItemList &items);
  bool GetGuideForChannel(const CStdString& base, CFileItemList &items, const int channelNumber);
  bool GetRecordings(const CStdString& base, CFileItemList &items, enum FilterType type = ALL, const CStdString& filter = "");
  bool GetTvShowFolders(const CStdString& base, CFileItemList &items);
  bool GetChannels(const CStdString& base, CFileItemList &items);

  CStdString GetValue(char* str)           { return m_session->GetValue(str); }
  CDateTime  GetValue(cmyth_timestamp_t t) { return m_session->GetValue(t); }
  bool IsVisible(const cmyth_proginfo_t program);
  bool IsMovie(const cmyth_proginfo_t program);
  bool IsTvShow(const cmyth_proginfo_t program);

  XFILE::CMythSession*  m_session;
  DllLibCMyth*          m_dll;
  cmyth_database_t      m_database;
  cmyth_recorder_t      m_recorder;
  cmyth_proginfo_t      m_program;
};

}
