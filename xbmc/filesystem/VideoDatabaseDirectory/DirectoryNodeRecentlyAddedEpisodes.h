#pragma once


#include "DirectoryNode.h"

namespace XFILE
{
  namespace VIDEODATABASEDIRECTORY
  {
    class CDirectoryNodeRecentlyAddedEpisodes : public CDirectoryNode
    {
    public:
      CDirectoryNodeRecentlyAddedEpisodes(const CStdString& strEntryName, CDirectoryNode* pParent);
    protected:
      virtual bool GetContent(CFileItemList& items) const;
      virtual NODE_TYPE GetChildType() const;
    };
  }
}


