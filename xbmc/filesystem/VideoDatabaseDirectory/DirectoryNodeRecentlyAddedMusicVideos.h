#pragma once


#include "DirectoryNode.h"

namespace XFILE
{
  namespace VIDEODATABASEDIRECTORY
  {
    class CDirectoryNodeRecentlyAddedMusicVideos : public CDirectoryNode
    {
    public:
      CDirectoryNodeRecentlyAddedMusicVideos(const CStdString& strEntryName, CDirectoryNode* pParent);
    protected:
      virtual bool GetContent(CFileItemList& items) const;
      virtual NODE_TYPE GetChildType() const;
    };
  }
}


