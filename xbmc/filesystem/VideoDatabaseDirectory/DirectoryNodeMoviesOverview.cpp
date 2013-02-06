

#include "DirectoryNodeMoviesOverview.h"
#include "FileItem.h"
#include "guilib/LocalizeStrings.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;
using namespace std;

Node MovieChildren[] = {
                        { NODE_TYPE_GENRE,        1, 135 },
                        { NODE_TYPE_TITLE_MOVIES, 2, 369 },
                        { NODE_TYPE_YEAR,         3, 562 },
                        { NODE_TYPE_ACTOR,        4, 344 },
                        { NODE_TYPE_DIRECTOR,     5, 20348 },
                        { NODE_TYPE_STUDIO,       6, 20388 },
                        { NODE_TYPE_SETS,         7, 20434 },
                        { NODE_TYPE_COUNTRY,      8, 20451 },
                       };

CDirectoryNodeMoviesOverview::CDirectoryNodeMoviesOverview(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_MOVIES_OVERVIEW, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeMoviesOverview::GetChildType() const
{
  for (unsigned int i = 0; i < sizeof(MovieChildren) / sizeof(Node); ++i)
    if (GetID() == MovieChildren[i].id)
      return MovieChildren[i].node;
  
  return NODE_TYPE_NONE;
}

CStdString CDirectoryNodeMoviesOverview::GetLocalizedName() const
{
  for (unsigned int i = 0; i < sizeof(MovieChildren) / sizeof(Node); ++i)
    if (GetID() == MovieChildren[i].id)
      return g_localizeStrings.Get(MovieChildren[i].label);
  return "";
}

bool CDirectoryNodeMoviesOverview::GetContent(CFileItemList& items) const
{
  for (unsigned int i = 0; i < sizeof(MovieChildren) / sizeof(Node); ++i)
  {
    if (i == 6)
    {
      CVideoDatabase db;
      if (db.Open() && !db.HasSets())
        continue;
    }
    CStdString path;
    path.Format("%s%ld/", BuildPath().c_str(), MovieChildren[i].id);
    CFileItemPtr pItem(new CFileItem(path, true));
    pItem->SetLabel(g_localizeStrings.Get(MovieChildren[i].label));
    pItem->SetCanQueue(false);
    items.Add(pItem);
  }

  return true;
}
