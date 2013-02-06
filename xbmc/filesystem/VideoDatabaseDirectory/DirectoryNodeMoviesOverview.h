#pragma once


#include "DirectoryNode.h"

namespace XFILE
{
  namespace VIDEODATABASEDIRECTORY
  {
    class CDirectoryNodeMoviesOverview : public CDirectoryNode
    {
    public:
      CDirectoryNodeMoviesOverview(const CStdString& strName, CDirectoryNode* pParent);
    protected:
      virtual NODE_TYPE GetChildType() const;
      virtual bool GetContent(CFileItemList& items) const;
      virtual CStdString GetLocalizedName() const;
    };
  }
}


