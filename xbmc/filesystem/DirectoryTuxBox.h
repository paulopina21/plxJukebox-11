#pragma once


#include "IDirectory.h"

class CURL;
class TiXmlElement;

namespace XFILE
{
  class CDirectoryTuxBox : public IDirectory
  {
    public:
      CDirectoryTuxBox(void);
      virtual ~CDirectoryTuxBox(void);
      virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
      virtual bool IsAllowed(const CStdString &strFile) const { return true; };
      virtual DIR_CACHE_TYPE GetCacheType(const CStdString& strPath) const { return DIR_CACHE_ALWAYS; };
    private:
      bool GetRootAndChildString(const CStdString strPath, CStdString& strBQRequest, CStdString& strXMLRootString, CStdString& strXMLChildString );
      void GetRootAndChildStringEnigma2(CStdString& strBQRequest, CStdString& strXMLRootString, CStdString& strXMLChildString );
  };
}

