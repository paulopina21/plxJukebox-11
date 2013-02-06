

#include "DirectoryNodeCountry.h"
#include "QueryParams.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeCountry::CDirectoryNodeCountry(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_COUNTRY, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeCountry::GetChildType() const
{
  return NODE_TYPE_TITLE_MOVIES;
}

CStdString CDirectoryNodeCountry::GetLocalizedName() const
{
  CVideoDatabase db;
  if (db.Open())
    return db.GetCountryById(GetID());
  return "";
}

bool CDirectoryNodeCountry::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  bool bSuccess=videodatabase.GetCountriesNav(BuildPath(), items, params.GetContentType());

  videodatabase.Close();

  return bSuccess;
}
