#pragma once


#include "DirectoryNode.h"

namespace XFILE
{
  namespace MUSICDATABASEDIRECTORY
  {
    class CDirectoryNodeRoot : public CDirectoryNode
    {
    public:
      CDirectoryNodeRoot(const CStdString& strName, CDirectoryNode* pParent);
    protected:
      virtual NODE_TYPE GetChildType() const;
    };
  }
}


