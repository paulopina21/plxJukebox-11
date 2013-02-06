

#include "SpecialProtocolDirectory.h"
#include "SpecialProtocol.h"
#include "Directory.h"
#include "utils/URIUtils.h"
#include "FileItem.h"

using namespace XFILE;

CSpecialProtocolDirectory::CSpecialProtocolDirectory(void)
{
}

CSpecialProtocolDirectory::~CSpecialProtocolDirectory(void)
{
}

bool CSpecialProtocolDirectory::GetDirectory(const CStdString& strPath, CFileItemList &items)
{
  CStdString untranslatedPath = strPath;  // Why do I need a copy??? - the GetDirectory() call below will override strPath???
  CStdString translatedPath = CSpecialProtocol::TranslatePath(strPath);
  if (CDirectory::GetDirectory(translatedPath, items, m_strFileMask, m_useFileDirectories, m_allowPrompting, m_cacheDirectory, m_extFileInfo, false, true))
  { // replace our paths as necessary
    items.SetPath(untranslatedPath);
    for (int i = 0; i < items.Size(); i++)
    {
      CFileItemPtr item = items[i];
      if (strnicmp(item->GetPath().c_str(), translatedPath.c_str(), translatedPath.GetLength()) == 0)
        item->SetPath(URIUtils::AddFileToFolder(untranslatedPath, item->GetPath().Mid(translatedPath.GetLength())));
    }
    return true;
  }
  return false;
}

bool CSpecialProtocolDirectory::Create(const char* strPath)
{
  CStdString translatedPath = CSpecialProtocol::TranslatePath(strPath);
  return CDirectory::Create(translatedPath.c_str());
}

bool CSpecialProtocolDirectory::Remove(const char* strPath)
{
  CStdString translatedPath = CSpecialProtocol::TranslatePath(strPath);
  return CDirectory::Remove(translatedPath.c_str());
}

bool CSpecialProtocolDirectory::Exists(const char* strPath)
{
  CStdString translatedPath = CSpecialProtocol::TranslatePath(strPath);
  return CDirectory::Exists(translatedPath.c_str());
}
