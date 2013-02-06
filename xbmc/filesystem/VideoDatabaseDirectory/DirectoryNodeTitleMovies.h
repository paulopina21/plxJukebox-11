#pragma once


#include "DirectoryNode.h"

namespace XFILE
{
  namespace VIDEODATABASEDIRECTORY
  {
    class CDirectoryNodeTitleMovies : public CDirectoryNode
    {
    public:
      CDirectoryNodeTitleMovies(const CStdString& strEntryName, CDirectoryNode* pParent);
    protected:
      virtual bool GetContent(CFileItemList& items) const;
    };
  }
}
