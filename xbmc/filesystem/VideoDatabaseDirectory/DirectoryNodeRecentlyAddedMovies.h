#pragma once


#include "DirectoryNode.h"

namespace XFILE
{
  namespace VIDEODATABASEDIRECTORY
  {
    class CDirectoryNodeRecentlyAddedMovies : public CDirectoryNode
    {
    public:
      CDirectoryNodeRecentlyAddedMovies(const CStdString& strEntryName, CDirectoryNode* pParent);
    protected:
      virtual bool GetContent(CFileItemList& items) const;
      virtual NODE_TYPE GetChildType() const;
    };
  }
}


