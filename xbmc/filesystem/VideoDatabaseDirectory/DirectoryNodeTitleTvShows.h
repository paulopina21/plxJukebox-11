#pragma once


#include "DirectoryNode.h"

namespace XFILE
{
  namespace VIDEODATABASEDIRECTORY
  {
    class CDirectoryNodeTitleTvShows : public CDirectoryNode
    {
    public:
      CDirectoryNodeTitleTvShows(const CStdString& strName, CDirectoryNode* pParent);
    protected:
      virtual NODE_TYPE GetChildType() const;
      virtual bool GetContent(CFileItemList& items) const;
      virtual CStdString GetLocalizedName() const;
    };
  }
}


