#pragma once


#include "IDirectory.h"
#include "tinyXML/tinyxml.h"
#include "FileItem.h"

namespace XFILE
{
  class CDAVDirectory : public IDirectory
  {
    public:
      CDAVDirectory(void);
      virtual ~CDAVDirectory(void);
      virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
      virtual bool Exists(const char* strPath);
      virtual DIR_CACHE_TYPE GetCacheType(const CStdString& strPath) const { return DIR_CACHE_ONCE; };
    private:
      bool ValueWithoutNamespace(const TiXmlNode *pNode, CStdString value);
      CStdString GetStatusTag(const TiXmlElement *pElement);
      void ParseResponse(const TiXmlElement *pElement, CFileItem &item);
  };
}
