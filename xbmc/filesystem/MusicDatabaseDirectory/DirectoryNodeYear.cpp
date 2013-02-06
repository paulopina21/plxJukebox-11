

#include "DirectoryNodeYear.h"
#include "QueryParams.h"
#include "music/MusicDatabase.h"

using namespace XFILE::MUSICDATABASEDIRECTORY;

CDirectoryNodeYear::CDirectoryNodeYear(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_YEAR, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeYear::GetChildType() const
{
  return NODE_TYPE_YEAR_ALBUM;
}

CStdString CDirectoryNodeYear::GetLocalizedName() const
{
  return GetName();
}

bool CDirectoryNodeYear::GetContent(CFileItemList& items) const
{
  CMusicDatabase musicdatabase;
  if (!musicdatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  bool bSuccess=musicdatabase.GetYearsNav(BuildPath(), items);

  musicdatabase.Close();

  return bSuccess;
}
