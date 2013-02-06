

#include "DirectoryNodeSets.h"
#include "QueryParams.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeSets::CDirectoryNodeSets(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_SETS, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeSets::GetChildType() const
{
  return NODE_TYPE_TITLE_MOVIES;
}

CStdString CDirectoryNodeSets::GetLocalizedName() const
{
  CVideoDatabase db;
  if (db.Open())
    return db.GetSetById(GetID());
  return "";
}

bool CDirectoryNodeSets::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  bool bSuccess=videodatabase.GetSetsNav(BuildPath(), items, params.GetContentType());

  videodatabase.Close();

  return bSuccess;
}
