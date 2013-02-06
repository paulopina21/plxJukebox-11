#pragma once


#include "IDirectory.h"

class CMediaSource;
typedef std::vector<CMediaSource> VECSOURCES;

namespace XFILE
{
  class CSourcesDirectory : public IDirectory
  {
  public:
    CSourcesDirectory(void);
    virtual ~CSourcesDirectory(void);
    virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
    bool GetDirectory(const VECSOURCES &sources, CFileItemList &items);
    virtual bool Exists(const char* strPath);
    virtual bool IsAllowed(const CStdString &strFile) const { return true; };
  };
}
