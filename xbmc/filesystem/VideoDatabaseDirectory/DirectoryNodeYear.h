#pragma once


#include "DirectoryNode.h"

namespace XFILE
{
  namespace VIDEODATABASEDIRECTORY
  {
    class CDirectoryNodeYear : public CDirectoryNode
    {
    public:
      CDirectoryNodeYear(const CStdString& strEntryName, CDirectoryNode* pParent);
    protected:
      virtual bool GetContent(CFileItemList& items) const;
      virtual NODE_TYPE GetChildType() const;
      virtual CStdString GetLocalizedName() const;
    };
  }
}


