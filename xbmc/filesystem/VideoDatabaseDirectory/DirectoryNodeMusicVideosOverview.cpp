

#include "DirectoryNodeMusicVideosOverview.h"
#include "FileItem.h"
#include "guilib/LocalizeStrings.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

Node MusicVideoChildren[] = {
                              { NODE_TYPE_GENRE,             1, 135 },
                              { NODE_TYPE_TITLE_MUSICVIDEOS, 2, 369 },
                              { NODE_TYPE_YEAR,              3, 562 },
                              { NODE_TYPE_ACTOR,             4, 133 },
                              { NODE_TYPE_MUSICVIDEOS_ALBUM, 5, 132 },
                              { NODE_TYPE_DIRECTOR,          6, 20348 },
                              { NODE_TYPE_STUDIO,            7, 20388 },
                            };

CDirectoryNodeMusicVideosOverview::CDirectoryNodeMusicVideosOverview(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_MUSICVIDEOS_OVERVIEW, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeMusicVideosOverview::GetChildType() const
{
  for (unsigned int i = 0; i < sizeof(MusicVideoChildren) / sizeof(Node); ++i)
    if (GetID() == MusicVideoChildren[i].id)
      return MusicVideoChildren[i].node;

  return NODE_TYPE_NONE;
}

CStdString CDirectoryNodeMusicVideosOverview::GetLocalizedName() const
{
  for (unsigned int i = 0; i < sizeof(MusicVideoChildren) / sizeof(Node); ++i)
    if (GetID() == MusicVideoChildren[i].id)
      return g_localizeStrings.Get(MusicVideoChildren[i].label);
  return "";
}

bool CDirectoryNodeMusicVideosOverview::GetContent(CFileItemList& items) const
{
  for (unsigned int i = 0; i < sizeof(MusicVideoChildren) / sizeof(Node); ++i)
  {
    CFileItemPtr pItem(new CFileItem(g_localizeStrings.Get(MusicVideoChildren[i].label)));
    CStdString strDir;
    strDir.Format("%ld/", MusicVideoChildren[i].id);
    pItem->SetPath(BuildPath() + strDir);
    pItem->m_bIsFolder = true;
    pItem->SetCanQueue(false);
    items.Add(pItem);
  }

  return true;
}

