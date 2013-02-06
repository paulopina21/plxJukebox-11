

#include "DirectoryNodeTvShowsOverview.h"
#include "FileItem.h"
#include "guilib/LocalizeStrings.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

Node TvShowChildren[] = {
                          { NODE_TYPE_GENRE,         1, 135 },
                          { NODE_TYPE_TITLE_TVSHOWS, 2, 369 },
                          { NODE_TYPE_YEAR,          3, 562 },
                          { NODE_TYPE_ACTOR,         4, 344 },
                          { NODE_TYPE_STUDIO,        5, 20388 },
                        };

CDirectoryNodeTvShowsOverview::CDirectoryNodeTvShowsOverview(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_TVSHOWS_OVERVIEW, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeTvShowsOverview::GetChildType() const
{
  if (GetName()=="0")
    return NODE_TYPE_EPISODES;

  for (unsigned int i = 0; i < sizeof(TvShowChildren) / sizeof(Node); ++i)
    if (GetID() == TvShowChildren[i].id)
      return TvShowChildren[i].node;

  return NODE_TYPE_NONE;
}

CStdString CDirectoryNodeTvShowsOverview::GetLocalizedName() const
{
  for (unsigned int i = 0; i < sizeof(TvShowChildren) / sizeof(Node); ++i)
    if (GetID() == TvShowChildren[i].id)
      return g_localizeStrings.Get(TvShowChildren[i].label);
  return "";
}

bool CDirectoryNodeTvShowsOverview::GetContent(CFileItemList& items) const
{
  for (unsigned int i = 0; i < sizeof(TvShowChildren) / sizeof(Node); ++i)
  {
    CFileItemPtr pItem(new CFileItem(g_localizeStrings.Get(TvShowChildren[i].label)));
    CStdString strDir;
    strDir.Format("%ld/", TvShowChildren[i].id);
    pItem->SetPath(BuildPath() + strDir);
    pItem->m_bIsFolder = true;
    pItem->SetCanQueue(false);
    items.Add(pItem);
  }

  return true;
}
