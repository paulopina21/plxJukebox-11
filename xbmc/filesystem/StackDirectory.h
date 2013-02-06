#pragma once



#include "IDirectory.h"
#include "utils/RegExp.h"

namespace XFILE
{
  class CStackDirectory : public IDirectory
  {
  public:
    CStackDirectory();
    ~CStackDirectory();
    virtual bool GetDirectory(const CStdString& strPath, CFileItemList& items);
    virtual bool IsAllowed(const CStdString &strFile) const { return true; };
    static CStdString GetStackedTitlePath(const CStdString &strPath);
    static CStdString GetStackedTitlePath(const CStdString &strPath, VECCREGEXP& RegExps);
    static CStdString GetFirstStackedFile(const CStdString &strPath);
    CStdString ConstructStackPath(const CFileItemList& items, const std::vector<int> &stack);
    bool ConstructStackPath(const std::vector<CStdString> &paths, CStdString &stackedPath);
  };
}
