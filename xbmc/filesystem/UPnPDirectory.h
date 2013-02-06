


#pragma once

#include "IDirectory.h"

class CFileItem;
class CURL;

namespace XFILE
{
class CUPnPDirectory :  public IDirectory
{
public:
    CUPnPDirectory(void) {}
    virtual ~CUPnPDirectory(void) {}

    // IDirectory methods
    virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
    virtual bool IsAllowed(const CStdString& strFile) const { return true; };

    // class methods
    static const char* GetFriendlyName(const char* url);
    static bool        GetResource(const CURL &path, CFileItem& item);
};
}
