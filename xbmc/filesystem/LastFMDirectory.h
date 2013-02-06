#pragma once


#include "IDirectory.h"
#include "FileCurl.h"
#include "tinyXML/tinyxml.h"
#include "threads/Thread.h"

class CGUIDialogProgress;

namespace XFILE
{
class CLastFMDirectory :
      public IDirectory, public IRunnable
{
public:
  CLastFMDirectory(void);
  virtual ~CLastFMDirectory(void);
  virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
  virtual void Run();

  virtual bool IsAllowed(const CStdString &strFile) const { return true; };
  virtual DIR_CACHE_TYPE GetCacheType(const CStdString& strPath) const;
protected:
  void AddEntry(int iString, CStdString strPath, CStdString strIconPath, bool bFolder, CFileItemList &items);
  void AddListEntry(const char *name, const char *artist, const char *count, const char *date, const char *icon, CStdString strPath, CFileItemList &items);
  CStdString BuildURLFromInfo();
  bool RetrieveList(CStdString url);
  bool ParseArtistList(CStdString url, CFileItemList &items);
  bool ParseAlbumList(CStdString url, CFileItemList &items);
  bool ParseUserList(CStdString url, CFileItemList &items);
  bool ParseTagList(CStdString url, CFileItemList &items);
  bool ParseTrackList(CStdString url, CFileItemList &items);

  bool GetArtistInfo(CFileItemList &items);
  bool GetUserInfo(CFileItemList &items);
  bool GetTagInfo(CFileItemList &items);

  bool SearchSimilarTags(CFileItemList &items);
  bool SearchSimilarArtists(CFileItemList &items);

  bool m_Error;
  bool m_Downloaded;
  TiXmlDocument m_xmlDoc;

  XFILE::CFileCurl m_http;

  CStdString m_objtype;
  CStdString m_objname;
  CStdString m_encodedobjname;
  CStdString m_objrequest;

  CStdString m_strSource;
  CStdString m_strDestination;

  CGUIDialogProgress* m_dlgProgress;
};
}
