

#include "DirectoryNodeRoot.h"

using namespace XFILE::MUSICDATABASEDIRECTORY;

CDirectoryNodeRoot::CDirectoryNodeRoot(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_ROOT, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeRoot::GetChildType() const
{
  return NODE_TYPE_OVERVIEW;
}
