#pragma once


#include "DirectoryNode.h"

namespace XFILE
{
  namespace MUSICDATABASEDIRECTORY
  {
    class CDirectoryNodeGenre : public CDirectoryNode
    {
    public:
      CDirectoryNodeGenre(const CStdString& strName, CDirectoryNode* pParent);
    protected:
      virtual NODE_TYPE GetChildType() const;
      virtual bool GetContent(CFileItemList& items) const;
      virtual CStdString GetLocalizedName() const;
    };
  }
}


