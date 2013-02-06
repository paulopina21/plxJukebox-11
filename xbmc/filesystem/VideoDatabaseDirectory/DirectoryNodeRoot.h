#pragma once


#include "DirectoryNode.h"

namespace XFILE
{
  namespace VIDEODATABASEDIRECTORY
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


